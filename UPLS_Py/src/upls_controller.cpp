#include "upls_controller.h"

#include <iostream>
#include <sstream>
#include <chrono>
#include <exception>
#include "logger.h"

using namespace na;
using namespace na::Console;

char const hex_chars[16] = { '0', '1', '2', '3', 
							 '4', '5', '6', '7', 
							 '8', '9', 'A', 'B', 
							 'C', 'D', 'E', 'F' };


UPLS_Controller::UPLS_Controller() : m_logReceivedPackets(false), m_receiverRunning(false), m_receiverThread(nullptr),
	m_hookInfoUpdateFrequency(0.f), m_landingGearInfoUpdateFrequency(0.f), 
	m_ledInfoUpdateFrequency(0.f), m_winchInfoUpdateFrequency(0.f),
	m_mainControllerInfoUpdateFrequency(0.f) { ; }

UPLS_Controller::~UPLS_Controller()
{
	if (m_receiverThread)
	{
		m_receiverRunning = false;
		m_receiverThread->join();
		delete m_receiverThread;
	}
	m_serial.close();
}

std::list<std::string> UPLS_Controller::listAvailablePorts()
{
	return SerialPort::listAvailablePorts();
}

void UPLS_Controller::printAvailablePorts()
{
	auto ports = SerialPort::listAvailablePorts();

	if (ports.empty())
		std::cout << "No ports found\n";
	else
		for (auto& port : ports)
			std::cout << port << std::endl;
}

void UPLS_Controller::setSerialPort(const char* portName)
{
	std::string str(portName);
	
	if (str.size() == 0)
		error("In UPLS_Controller::setSerialPort(std::string& portName). portName.size() returned: 0");

	m_serial.setPort(str);
}

bool UPLS_Controller::start()
{
	m_serial.setBaudRate(SerialPort::BaudRate::Baud115200);
	m_serial.setDataBits(SerialPort::DataBits::Eight);
	m_serial.setFlowControl(SerialPort::FlowControl::Disabled);
	m_serial.setParity(SerialPort::Parity::Disabled);
	m_serial.setStopBits(SerialPort::StopBits::One);

	bool ok = m_serial.open();

	if (ok)
	{
		if (m_receiverThread != nullptr)
		{
			m_receiverRunning = false;
			m_receiverThread->join();
			delete m_receiverThread;
		}

		info("Launching packet handler thread...");
		m_receiverRunning = true;
		m_receiverThread = new std::thread(&UPLS_Controller::m_receivedPacketHandler, this);

		Packet packet = PacketHandler::createCommand(Command(Command::StartCommunication), Device::MainController);
		m_serial.write(&packet, sizeof(Packet));
	}
	else
	{
		error("Failed to open serial port.");
	}

	auto packet = PacketHandler::createCommand(Command::StartCommunication, Device::MainController);
	m_serial.write(&packet, sizeof(Packet));

	return ok;
}

void UPLS_Controller::stop()
{
	auto packet = PacketHandler::createCommand(Command::EndCommunication, Device::MainController);
	m_serial.write(&packet, sizeof(Packet));
	
	m_receiverRunning = false;
	
	if (m_receiverThread)
	{
		m_receiverThread->join();
		delete m_receiverThread;
		m_receiverThread = nullptr;
	}

	m_serial.close();

	m_hookInfoUpdateFrequency = 0.f;
	m_landingGearInfoUpdateFrequency = 0.f;
	m_ledInfoUpdateFrequency = 0.f;
	m_winchInfoUpdateFrequency = 0.f;

	m_hookInfo = HookInfo();
	m_landingGearInfo = LandingGearInfo();
	m_ledInfo = LedInfo();
	m_winchInfo = WinchInfo();
}

bool UPLS_Controller::receivedPacketLoggingEnabled()
{
	return m_logReceivedPackets;
}

void UPLS_Controller::enableReceivedPacketLogging(bool enable)
{
	m_logReceivedPackets = enable;
}

bool UPLS_Controller::errorsOccured()
{
	return !m_errorQueue.empty();
}

Error UPLS_Controller::getError()
{
	return m_errorQueue.pop().error;
}

void UPLS_Controller::printError()
{
	auto error_packet = m_errorQueue.pop();

	log.info(Format("UPLS_Controller").color(Color::BrightMagenta).bold(), ": ", 
			Format("Error").color(Format::Color::BrightRed), " from ", 
			Format(device(error_packet.sender)).color(Color::Yellow), ": '",
			errorMessage(error_packet.error.getCode()), '\'');
}

void UPLS_Controller::printAllErrors()
{
	for (auto error_packet : m_errorQueue)
	{
		log.info(Format("UPLS_Controller").color(Color::BrightMagenta).bold(), ": ", 
			Format("Error").color(Format::Color::BrightRed), " from ", 
			Format(device(error_packet.sender)).color(Color::Yellow), ": '",
			errorMessage(error_packet.error.getCode()), '\'');
	}
}

void UPLS_Controller::clearAllErrors()
{
	m_errorQueue.clear();
}

bool UPLS_Controller::warningsReceived()
{
	return !m_warningQueue.empty();
}

void UPLS_Controller::printWarning()
{
	auto warning_packet = m_warningQueue.pop();

	log.info(Format("UPLS_Controller").color(Color::BrightMagenta).bold(), ": ", 
			Format("Warning").color(Format::Color::Yellow), " from ", 
			Format(device(warning_packet.sender)).color(Color::Yellow), ": '",
			warningMessage(warning_packet.warning.getCode()), '\'');
}

void UPLS_Controller::printAllWarnings()
{
	for (auto warning_packet : m_warningQueue)
	{
		log.info(Format("UPLS_Controller").color(Color::BrightMagenta).bold(), ": ", 
			Format("Warning").color(Format::Color::Yellow), " from ", 
			Format(device(warning_packet.sender)).color(Color::Yellow), ": '",
			warningMessage(warning_packet.warning.getCode()), '\'');
	}
}

void UPLS_Controller::clearAllWarnings()
{
	m_warningQueue.clear();
}

bool UPLS_Controller::messagesReceived()
{
	return !m_messageQueue.empty();
}

void UPLS_Controller::printAllMessages()
{
	while (!m_messageQueue.empty())
	{
		auto message_packet = m_messageQueue.pop();

		log.info(Format("UPLS_Controller").color(Color::BrightMagenta).bold(), ": ", 
			Format("Message").color(Format::Color::Magenta), " from ", 
			Format(device(message_packet.sender)).color(Color::Yellow), ": '", message_packet.message, '\'');
	}
}

HookInfo UPLS_Controller::hookInfo()
{
	std::shared_lock<std::shared_mutex> lock(muxHookInfo);
	return m_hookInfo;
}

LandingGearInfo UPLS_Controller::landingGearInfo()
{
	std::shared_lock<std::shared_mutex> lock(muxLandingGearInfo);
	return m_landingGearInfo;
}
	
LedInfo UPLS_Controller::ledInfo()
{
	std::shared_lock<std::shared_mutex> lock(muxLedInfo);
	return m_ledInfo;
}
	
WinchInfo UPLS_Controller::winchInfo()
{
	std::shared_lock<std::shared_mutex> lock(muxWinchInfo);
	return m_winchInfo;
}

MainControllerInfo UPLS_Controller::mainControllerInfo()
{
	std::shared_lock<std::shared_mutex> lock(muxMainControllerInfo);
	return m_mainControllerInfo;
}

float UPLS_Controller::hookInfoUpdateFrequency()
{
	std::chrono::duration<int64_t, std::nano> delta_time;
	std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::steady_clock::now();
	
	{
		std::shared_lock<std::shared_mutex> lock(muxHookInfo);
		delta_time = now - m_lastHookInfoUpdateTimePoint;
	}
	
	float period_ms = 1000.f / m_hookInfoUpdateFrequency;
	if (float(std::chrono::duration_cast<std::chrono::milliseconds>(delta_time).count()) > period_ms * 1.4f)
	{
		m_hookInfoUpdateFrequency = 0.f;
		std::unique_lock<std::shared_mutex> lock(muxHookInfo);
		m_hookInfo = HookInfo();
	}

	return m_hookInfoUpdateFrequency;
}

float UPLS_Controller::landingGearInfoUpdateFrequency()
{
	std::chrono::duration<int64_t, std::nano> delta_time;
	std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::steady_clock::now();
	
	{
		std::shared_lock<std::shared_mutex> lock(muxLandingGearInfo);
		delta_time = now - m_lastLandingGearInfoUpdateTimePoint;
	}
	
	float period_ms = 1000.f / m_landingGearInfoUpdateFrequency;
	if (float(std::chrono::duration_cast<std::chrono::milliseconds>(delta_time).count()) > period_ms * 1.4f)
	{
		m_landingGearInfoUpdateFrequency = 0.f;
		std::unique_lock<std::shared_mutex> lock(muxLandingGearInfo);
		m_landingGearInfo = LandingGearInfo();
	}

	return m_landingGearInfoUpdateFrequency;
}

float UPLS_Controller::ledInfoUpdateFrequency()
{
	std::chrono::duration<int64_t, std::nano> delta_time;
	std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::steady_clock::now();
	
	{
		std::shared_lock<std::shared_mutex> lock(muxLedInfo);
		delta_time = now - m_lastLedInfoUpdateTimePoint;
	}
	
	float period_ms = 1000.f / m_ledInfoUpdateFrequency;
	if (float(std::chrono::duration_cast<std::chrono::milliseconds>(delta_time).count()) > period_ms * 1.4f)
	{
		m_ledInfoUpdateFrequency = 0.f;
		std::unique_lock<std::shared_mutex> lock(muxLedInfo);
		m_ledInfo = LedInfo();
	}

	return m_ledInfoUpdateFrequency;
}

float UPLS_Controller::winchInfoUpdateFrequency()
{
	std::chrono::duration<int64_t, std::nano> delta_time;
	std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::steady_clock::now();
	
	{
		std::shared_lock<std::shared_mutex> lock(muxWinchInfo);
		delta_time = now - m_lastWinchInfoUpdateTimePoint;
	}
	
	float period_ms = 1000.f / m_winchInfoUpdateFrequency;
	if (float(std::chrono::duration_cast<std::chrono::milliseconds>(delta_time).count()) > period_ms * 1.4f)
	{
		m_winchInfoUpdateFrequency = 0.f;
		std::unique_lock<std::shared_mutex> lock(muxWinchInfo);
		m_winchInfo = WinchInfo();
	}

	return m_winchInfoUpdateFrequency;
}

float UPLS_Controller::mainControllerInfoUpdateFrequency()
{
	std::chrono::duration<int64_t, std::nano> delta_time;
	std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::steady_clock::now();
	
	{
		std::shared_lock<std::shared_mutex> lock(muxMainControllerInfo);
		delta_time = now - m_lastMainControllerInfoUpdateTimePoint;
	}
	
	float period_ms = 1000.f / m_mainControllerInfoUpdateFrequency;
	if (float(std::chrono::duration_cast<std::chrono::milliseconds>(delta_time).count()) > period_ms * 1.4f)
	{
		m_mainControllerInfoUpdateFrequency = 0.f;
		std::unique_lock<std::shared_mutex> lock(muxMainControllerInfo);
		m_mainControllerInfo = MainControllerInfo();
	}

	return m_mainControllerInfoUpdateFrequency;
}

void UPLS_Controller::ledsOn()
{
	Packet packet;
	packet = PacketHandler::createCommand(Command(Command::LedsOnAll));
	m_serial.write(&packet, sizeof(Packet));
}

void UPLS_Controller::ledsOff()
{
	Packet packet;
	packet = PacketHandler::createCommand(Command(Command::LedsOffAll));
	m_serial.write(&packet, sizeof(Packet));
}

void UPLS_Controller::ledsEnable()
{
	Packet packet = PacketHandler::createCommand(Command(Command::LedsEnableAll));
	m_serial.write(&packet, sizeof(Packet));
}

void UPLS_Controller::ledsDisable()
{
	Packet packet = PacketHandler::createCommand(Command(Command::LedsDisableAll));
	m_serial.write(&packet, sizeof(Packet));
}

void UPLS_Controller::ledsSetMode(LedInfo::Led::Mode mode)
{
	Packet packet = PacketHandler::createCommand(
		Command(Command::LedsSetModeAll).setLedMode(mode) );
	m_serial.write(&packet, sizeof(Packet));
}

void UPLS_Controller::ledsSetSettings(LedInfo::Led::Settings settings)
{
	Packet packet = PacketHandler::createCommand(
		Command(Command::LedsSetSettingsAll).setLedSettings(settings) );
	m_serial.write(&packet, sizeof(Packet));
}

void UPLS_Controller::latchOpen()
{
	Packet packet;
	packet = PacketHandler::createCommand(Command(Command::LatchOpen), Device::Hook);
	m_serial.write(&packet, sizeof(Packet));
}

void UPLS_Controller::latchClose()
{
	Packet packet;
	packet = PacketHandler::createCommand(Command(Command::LatchClose), Device::Hook);
	m_serial.write(&packet, sizeof(Packet));
}

void UPLS_Controller::latchSetOpenPulseDuration(int pulse_duration)
{
	Packet packet;
	packet = PacketHandler::createCommand(Command(Command::SetLatchOpenPulseDuration).setPulseLength(pulse_duration), Device::Hook);
	m_serial.write(&packet, sizeof(Packet));
}

void UPLS_Controller::latchSetClosePulseDuration(int pulse_duration)
{
	Packet packet;
	packet = PacketHandler::createCommand(Command(Command::SetLatchClosePulseDuration).setPulseLength(pulse_duration), Device::Hook);
	m_serial.write(&packet, sizeof(Packet));
}

void UPLS_Controller::hookShutdown()
{
	Packet packet;
	packet = PacketHandler::createCommand(Command(Command::HookShutdown), Device::Hook);
	m_serial.write(&packet, sizeof(Packet));
}

void UPLS_Controller::landingGearExtract()
{
	Packet packet;
	packet = PacketHandler::createCommand(Command(Command::Code::LandingGearExtract));
	m_serial.write(&packet, sizeof(Packet));
}

void UPLS_Controller::landingGearRetract()
{
	Packet packet;
	packet = PacketHandler::createCommand(Command(Command::Code::LandingGearRetract));
	m_serial.write(&packet, sizeof(Packet));
}

void UPLS_Controller::winchManualUp(float speed, float duration)
{
	Packet packet;
	packet = PacketHandler::createCommand(
		Command(Command::Code::WinchManualUp).setWinchManualSpeedAndDuration(speed, duration));
	m_serial.write(&packet, sizeof(Packet));
}

void UPLS_Controller::winchManualDown(float speed, float duration)
{
	Packet packet;
	packet = PacketHandler::createCommand(
		Command(Command::Code::WinchManualDown).setWinchManualSpeedAndDuration(speed, duration));
	m_serial.write(&packet, sizeof(Packet));
}

void UPLS_Controller::winchLower(float distance)
{
	Packet packet;
	packet = PacketHandler::createCommand(
		Command(Command::Code::WinchLower).setWinchLowerDistance(distance));
	m_serial.write(&packet, sizeof(Packet));
}

void UPLS_Controller::winchHome()
{
	Packet packet;
	packet = PacketHandler::createCommand(
		Command(Command::Code::WinchHome));
	m_serial.write(&packet, sizeof(Packet));
}

void UPLS_Controller::winchHalt()
{
	Packet packet;
	packet = PacketHandler::createCommand(
		Command(Command::Code::WinchHalt));
	m_serial.write(&packet, sizeof(Packet));
}

void UPLS_Controller::winchResume()
{
	Packet packet;
	packet = PacketHandler::createCommand(
		Command(Command::Code::WinchResume));
	m_serial.write(&packet, sizeof(Packet));
}

void UPLS_Controller::winchManualModeEnable()
{
	Packet packet;
	packet = PacketHandler::createCommand(
		Command(Command::Code::WinchManualModeEnable));
	m_serial.write(&packet, sizeof(Packet));
}

void UPLS_Controller::winchManualModeDisable()
{
	Packet packet;
	packet = PacketHandler::createCommand(
		Command(Command::Code::WinchManualModeDisable));
	m_serial.write(&packet, sizeof(Packet));
}

void UPLS_Controller::error(const char* error_msg)
{
	log.error(Format("UPLS_Controller").color(Color::BrightMagenta).bold(), ": ", error_msg); 
}

void UPLS_Controller::warning(const char* warning_msg)
{
	log.warning(Format("UPLS_Controller").color(Color::BrightMagenta).bold(), ": ", warning_msg); 
}

void UPLS_Controller::message(const char* msg)
{
	log.info(Format("UPLS_Controller").color(Color::BrightMagenta).bold(), ": ", msg); 
}

/************************* PRIVATE MEMBER FUNCTIONS ***************************/

void UPLS_Controller::m_receivedPacketHandler()
{
	log.info(Format("UPLS_Controller").color(Color::BrightMagenta).bold(), ": Packet handler thread started. Thread ID: ",
		Format().color(Color::Yellow), std::hex, std::this_thread::get_id(), std::dec, Format());

	PacketHandler handler;
	
	while (m_receiverRunning)
	{
		while (m_serial.available())
			handler.parseChar(m_serial.getChar());

		while (handler.packetAvailable())
		{
			Packet packet;
			packet = handler.getPacket();

			switch (packet.type)
			{
			case Packet::Type::HookInfo:
				m_updateHookInfo(packet.hook);
				if (m_logReceivedPackets) 
				{
					log.debug(Format("UPLS_Controller").color(Color::BrightMagenta).bold(), ": Packet received. Type: ",
						Format("HookInfo").color(Color::Green), " Sender: ", Format(device(packet.sender)).color(Color::Yellow));
				}
				break;

			case Packet::Type::LandingGearInfo:
				m_updateLandingGearInfo(packet.landingGear);
				if (m_logReceivedPackets) 
				{
					log.debug(Format("UPLS_Controller").color(Color::BrightMagenta).bold(), ": Packet received. Type: ",
						Format("LandingGearInfo").color(Color::Green), " Sender: ", Format(device(packet.sender)).color(Color::Yellow));
				}
				break;

			case Packet::Type::LedInfo:
				m_updateLedInfo(packet.led);
				if (m_logReceivedPackets) 
				{
					log.debug(Format("UPLS_Controller").color(Color::BrightMagenta).bold(), ": Packet received. Type: ",
						Format("LedInfo").color(Color::Green), " Sender: ", Format(device(packet.sender)).color(Color::Yellow));
				}
				break;

			case Packet::Type::WinchInfo:
				m_updateWinchInfo(packet.winch);
				if (m_logReceivedPackets) 
				{
					log.debug(Format("UPLS_Controller").color(Color::BrightMagenta).bold(), ": Packet received. Type: ",
						Format("WinchInfo").color(Color::Green), " Sender: ", Format(device(packet.sender)).color(Color::Yellow));
				}
				break;

			case Packet::Type::MainControllerInfo:
				m_updateMainControllerInfo(packet.mainController);
				if (m_logReceivedPackets) 
				{
					log.debug(Format("UPLS_Controller").color(Color::BrightMagenta).bold(), ": Packet received. Type: ",
						Format("MainControllerInfo").color(Color::Green), " Sender: ", Format(device(packet.sender)).color(Color::Yellow));
				}
				break;

			case Packet::Type::Error:
				m_errorQueue.push(packet);
				if (m_logReceivedPackets) 
				{
					log.debug(Format("UPLS_Controller").color(Color::BrightMagenta).bold(), ": Packet received. Type: ",
						Format("Error").color(Color::Green), " Sender: ", Format(device(packet.sender)).color(Color::Yellow));
				}
				break;

			case Packet::Type::Warning:
				m_warningQueue.push(packet);
				if (m_logReceivedPackets) 
				{
					log.debug(Format("UPLS_Controller").color(Color::BrightMagenta).bold(), ": Packet received. Type: ",
						Format("Warning").color(Color::Green), " Sender: ", Format(device(packet.sender)).color(Color::Yellow));
				}
				break;

			case Packet::Type::Message:
				m_messageQueue.push(packet);
				if (m_logReceivedPackets) 
				{
					log.debug(Format("UPLS_Controller").color(Color::BrightMagenta).bold(), ": Packet received. Type: ",
						Format("Message").color(Color::Green), " Sender: ", Format(device(packet.sender)).color(Color::Yellow));
				}
				break;

			default:
				if (m_logReceivedPackets) 
				{
					log.debug(Format("UPLS_Controller").color(Color::BrightMagenta).bold(), ": Packet received. Type: ",
						Format("Unknown").color(Color::Red), " Sender: ", Format(device(packet.sender)).color(Color::Yellow));
				}
				break;
			}
		}
	}
	log.info(Format("UPLS_Controller").color(Color::BrightMagenta).bold(), ": Packet handler thread exiting... Thread ID: ",
		Format().color(Color::Yellow), std::hex, std::this_thread::get_id(), std::dec, Format());
}

void UPLS_Controller::m_updateHookInfo(HookInfo& info)
{
	auto newTimePoint = std::chrono::steady_clock::now();

	std::unique_lock<std::shared_mutex> lock(muxHookInfo);

	auto delta_time = newTimePoint - m_lastHookInfoUpdateTimePoint;
	m_lastHookInfoUpdateTimePoint = newTimePoint;

	float f = 1000000.f / float(std::chrono::duration_cast<std::chrono::microseconds>(delta_time).count());
	m_hookInfoUpdateFrequency = f > 0.0001f ? f : 0.f;
	m_hookInfo = info;
}

void UPLS_Controller::m_updateLandingGearInfo(LandingGearInfo& info)
{
	auto newTimePoint = std::chrono::steady_clock::now();

	std::unique_lock<std::shared_mutex> lock(muxLandingGearInfo);

	auto delta_time = newTimePoint - m_lastLandingGearInfoUpdateTimePoint;
	m_lastLandingGearInfoUpdateTimePoint = newTimePoint;

	float f = 1000000.f / float(std::chrono::duration_cast<std::chrono::microseconds>(delta_time).count());
	m_landingGearInfoUpdateFrequency = f > 0.0001f ? f : 0.f;
	
	m_landingGearInfo = info;
}

void UPLS_Controller::m_updateLedInfo(LedInfo& info)
{
	auto newTimePoint = std::chrono::steady_clock::now();

	std::unique_lock<std::shared_mutex> lock(muxLedInfo);

	auto delta_time = newTimePoint - m_lastLedInfoUpdateTimePoint;
	m_lastLedInfoUpdateTimePoint = newTimePoint;

	float f = 1000000.f / float(std::chrono::duration_cast<std::chrono::microseconds>(delta_time).count());
	m_ledInfoUpdateFrequency = f > 0.0001f ? f : 0.f;
	
	m_ledInfo = info;
}

void UPLS_Controller::m_updateWinchInfo(WinchInfo& info)
{
	auto newTimePoint = std::chrono::steady_clock::now();
	
	std::unique_lock<std::shared_mutex> lock(muxWinchInfo);
	
	auto delta_time = newTimePoint - m_lastWinchInfoUpdateTimePoint;
	m_lastWinchInfoUpdateTimePoint = newTimePoint;

	float f = 1000000.f / float(std::chrono::duration_cast<std::chrono::microseconds>(delta_time).count());
	m_winchInfoUpdateFrequency = f > 0.0001f ? f : 0.f;
	
	m_winchInfo = info;
}

void UPLS_Controller::m_updateMainControllerInfo(MainControllerInfo& info)
{
	auto newTimePoint = std::chrono::steady_clock::now();

	std::unique_lock<std::shared_mutex> lock(muxMainControllerInfo);
	
	auto delta_time = newTimePoint - m_lastMainControllerInfoUpdateTimePoint;
	m_lastMainControllerInfoUpdateTimePoint = newTimePoint;

	float f = 1000000.f / float(std::chrono::duration_cast<std::chrono::microseconds>(delta_time).count());
	m_mainControllerInfoUpdateFrequency = f > 0.0001f ? f : 0.f;
	
	m_mainControllerInfo = info;
}


void UPLS_Controller::info(const char* info_msg)
{
	log.info(Format("UPLS_Controller").color(Color::BrightMagenta).bold(), ": ", info_msg); 
}