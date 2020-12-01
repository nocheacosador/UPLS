#include "upls_controller.h"

#include <iostream>
#include <sstream>
#include <chrono>
#include "console_formating.h"

char const hex_chars[16] = { '0', '1', '2', '3', 
							 '4', '5', '6', '7', 
							 '8', '9', 'A', 'B', 
							 'C', 'D', 'E', 'F' };


UPLS_Controller::UPLS_Controller() : m_receiverThread(nullptr), m_receiverRunning(false), m_hookInfoUpdateFrequency(0.f),
	m_landingGearInfoUpdateFrequency(0.f), m_ledInfoUpdateFrequency(0.f), m_winchInfoUpdateFrequency(0.f) { ; }

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
	m_serial.setBaudRate(SerialPort::BaudRate::Baud38400);
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
	}
	else
	{
		error("Failed to open serial port.");
	}

	return ok;
}

void UPLS_Controller::stop()
{
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

bool UPLS_Controller::errorsOccured()
{
	return !m_errorQueue.empty();
}

void UPLS_Controller::printError()
{
	auto error_packet = m_errorQueue.pop();

	std::cout << '[' << Format().color(Format::Color::BrightRed).bold().text("ERROR") << "] in: " 
		<< device(error_packet.sender) << ": " << errorMessage(error_packet.error.getCode()) << '\n';
}

void UPLS_Controller::printAllErrors()
{
	for (auto error_packet : m_errorQueue)
	{
		std::cout << '[' << Format().color(Format::Color::BrightRed).bold().text("ERROR") << "] in: " 
			<< device(error_packet.sender) << ": " << errorMessage(error_packet.error.getCode()) << '\n';
	}
}

void UPLS_Controller::clearAllErrors()
{
	m_errorQueue.clear();
}

/*int UPLS_Controller::popError()
{
	return 0; //error code
}*/

bool UPLS_Controller::warningsReceived()
{
	return !m_warningQueue.empty();
}

void UPLS_Controller::printWarning()
{
	auto warning_packet = m_warningQueue.pop();

	std::cout << '[' << Format().color(Format::Color::Yellow).bold().text("WARNING") << "] in: " 
		<< device(warning_packet.sender) << ": " << warningMessage(warning_packet.warning.getCode()) << '\n';
}

void UPLS_Controller::printAllWarnings()
{
	for (auto warning_packet : m_warningQueue)
	{
		std::cout << '[' << Format().color(Format::Color::Yellow).bold().text("WARNING") << "] in: " 
			<< device(warning_packet.sender) << ": " << warningMessage(warning_packet.warning.getCode()) << '\n';
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

		std::cout << '[' << Format().color(Format::Color::Magenta).bold().text("MESSAGE") << "] from: " 
			<< device(message_packet.sender) << ": " << message_packet.message << '\n';
	}
}

HookInfo UPLS_Controller::hookInfo()
{
	std::scoped_lock lock(muxHookinfo);
	return m_hookInfo;
}

LandingGearInfo UPLS_Controller::landingGearInfo()
{
	std::scoped_lock lock(muxLandingGearInfo);
	return m_landingGearInfo;
}
	
LedInfo UPLS_Controller::ledInfo()
{
	std::scoped_lock lock(muxLedInfo);
	return m_ledInfo;
}
	
WinchInfo UPLS_Controller::winchInfo()
{
	std::scoped_lock lock(muxWinchInfo);
	return m_winchInfo;
}


float UPLS_Controller::hookInfoUpdateFrequency()
{
	return m_hookInfoUpdateFrequency;
}

float UPLS_Controller::landingGearInfoUpdateFrequency()
{
	return m_landingGearInfoUpdateFrequency;
}

float UPLS_Controller::ledInfoUpdateFrequency()
{
	return m_ledInfoUpdateFrequency;
}

float UPLS_Controller::winchInfoUpdateFrequency()
{
	return m_winchInfoUpdateFrequency;
}

void UPLS_Controller::ledOn()
{
	Packet packet;
	packet = PacketHandler::createCommand(Command(Command::Code::LedsOn));
	m_serial.write(&packet, sizeof(Packet));
}

void UPLS_Controller::ledOff()
{
	Packet packet;
	packet = PacketHandler::createCommand(Command(Command::Code::LedsOff));
	m_serial.write(&packet, sizeof(Packet));
}

void UPLS_Controller::error(const char* error_msg)
{
	std::cout << '[' << Format().bold().color(Format::Color::BrightRed).text("ERROR") << "] " << error_msg << '\n'; 
}

void UPLS_Controller::warning(const char* warning_msg)
{
	std::cout << '[' << Format().bold().color(Format::Color::BrightYellow).text("WARNING") << "] " << warning_msg << '\n'; 
}

void UPLS_Controller::message(const char* msg)
{
	std::cout << '[' << Format().bold().color(Format::Color::BrightGreen).text("MESSAGE") << "] " << msg << '\n'; 
}

/************************* PRIVATE MEMBER FUNCTIONS ***************************/

void UPLS_Controller::m_receivedPacketHandler()
{
	info("Packet handler thread started.");
	
	PacketHandler handler;
	
	while (m_receiverRunning)
	{
		while (m_serial.available())
			handler.parseChar(m_serial.getChar());

		while (handler.packetAvailable())
		{
			auto packet = handler.getPacket();

			std::stringstream ss;
			ss << "Packet received. Type: ";

			switch (packet.type)
			{
			case Packet::Type::HookInfo:
				m_updateHookInfo(packet.hook);
				ss << Format("HookInfo").color(Color::Green);
				break;

			case Packet::Type::LandingGearInfo:
				m_updateLandingGearInfo(packet.landingGear);
				ss << Format("LandingGearInfo").color(Color::Green);
				break;

			case Packet::Type::LedInfo:
				m_updateLedInfo(packet.led);
				ss << Format("LedInfo").color(Color::Green);
				break;

			case Packet::Type::WinchInfo:
				m_updateWinchInfo(packet.winch);
				ss << Format("WinchInfo").color(Color::Green);
				break;

			case Packet::Type::Error:
				m_errorQueue.push(packet);
				ss << Format("Error").color(Color::Green);
				break;

			case Packet::Type::Warning:
				m_warningQueue.push(packet);
				ss << Format("Warning").color(Color::Green);
				break;

			case Packet::Type::Message:
				m_messageQueue.push(packet);
				ss << Format("Message").color(Color::Green);
				break;

			default:
				ss << Format("Unknown").color(Color::Red);
				break;
			}

			info(ss.str().c_str());
		}
	}

	info("Packet handler thread exiting...");
}

void UPLS_Controller::m_updateHookInfo(HookInfo& info)
{
	auto newTimePoint = std::chrono::steady_clock::now();
	auto delta_time = newTimePoint - m_lastHookInfoUpdateTimePoint;
	m_lastHookInfoUpdateTimePoint = newTimePoint;

	float f = 1000000.f / float(std::chrono::duration_cast<std::chrono::microseconds>(delta_time).count());
	m_hookInfoUpdateFrequency = f > 0.0001f ? f : 0.f;

	std::scoped_lock lock(muxHookinfo);
	m_hookInfo = info;
}

void UPLS_Controller::m_updateLandingGearInfo(LandingGearInfo& info)
{
	auto newTimePoint = std::chrono::steady_clock::now();
	auto delta_time = newTimePoint - m_lastLandingGearInfoUpdateTimePoint;
	m_lastLandingGearInfoUpdateTimePoint = newTimePoint;

	float f = 1000000.f / float(std::chrono::duration_cast<std::chrono::microseconds>(delta_time).count());
	m_landingGearInfoUpdateFrequency = f > 0.0001f ? f : 0.f;
	
	std::scoped_lock lock(muxLandingGearInfo);
	m_landingGearInfo = info;
}

void UPLS_Controller::m_updateLedInfo(LedInfo& info)
{
	auto newTimePoint = std::chrono::steady_clock::now();
	auto delta_time = newTimePoint - m_lastLedInfoUpdateTimePoint;
	m_lastLedInfoUpdateTimePoint = newTimePoint;

	float f = 1000000.f / float(std::chrono::duration_cast<std::chrono::microseconds>(delta_time).count());
	m_ledInfoUpdateFrequency = f > 0.0001f ? f : 0.f;
	
	std::scoped_lock lock(muxLedInfo);
	m_ledInfo = info;
}

void UPLS_Controller::m_updateWinchInfo(WinchInfo& info)
{
	auto newTimePoint = std::chrono::steady_clock::now();
	auto delta_time = newTimePoint - m_lastWinchInfoUpdateTimePoint;
	m_lastWinchInfoUpdateTimePoint = newTimePoint;

	float f = 1000000.f / float(std::chrono::duration_cast<std::chrono::microseconds>(delta_time).count());
	m_winchInfoUpdateFrequency = f > 0.0001f ? f : 0.f;
	
	std::scoped_lock lock(muxWinchInfo);
	m_winchInfo = info;
}

void UPLS_Controller::info(const char* info_msg)
{
	std::scoped_lock<std::mutex> lock(muxInfoStream);
	std::cout << '[' << Format().bold().color(Format::Color::BrightCyan).text("UPLS_Controller") << "] " << info_msg << '\n'; 
}