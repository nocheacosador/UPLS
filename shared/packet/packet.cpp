#include "packet.h"

Command::Command() : code(Command::Code::Unknown), pulseLength(0) { ; }
Command::Command(Command::Code _code) : code(_code), pulseLength(0) { ; }

#if defined(__XAVIER)
//void HookInfo::Battery::setVoltage(uint16_t _voltage) { voltage = _voltage; }
//void HookInfo::Battery::setState(State _state) { state = _state; }
float HookInfo::Battery::getVoltage() const { return float(voltage) / 1000.f; }
HookInfo::Battery::State HookInfo::Battery::getState() const { return state; }
HookInfo::Battery::Battery(uint16_t _voltage, HookInfo::Battery::State _state) : voltage(_voltage), state(_state) { ; }
#endif // __XAVIER

HookInfo::HookInfo() : averageRetrie(0.f), mcuRuntime(0.f), lostMessages(0), 
	temperature(0), battery({ 0, Battery::State::Unknown }), latch({ Latch::State::Unknown, 0 }) { ; }

#if !defined(__HOOK)
LedInfo::LedInfo() { memset(this, 0, sizeof(LedInfo)); }

LandingGearInfo::LandingGearInfo() { memset(this, 0, sizeof(LandingGearInfo)); } 

WinchInfo::WinchInfo() : current(0), position(0), status(WinchInfo::Status::Unknown) { ; }
#endif // !__HOOK

Error::Error() : code(Error::Code::Other), message("") { ; }
Error::Error(Error::Code _code) : code(_code), message("") { ; }
Error::Error(Error::Code _code, const char* msg) : code(_code) 
{
	uint8_t i = 0;
	while (i < 30 && msg[i] != '\n' && msg[i] != '\0' && msg[i] != '\r')
	{
		message[i] = msg[i];
		i++;
	}
	message[i] = '\0';
}

Warning::Warning() : code(Warning::Code::Other), message("") { ; }
Warning::Warning(Warning::Code _code) : code(_code), message("") { ; }
Warning::Warning(Warning::Code _code, const char* msg) : code(_code) 
{
	uint8_t i = 0;
	while (i < 30 && msg[i] != '\n' && msg[i] != '\0' && msg[i] != '\r')
	{
		message[i] = msg[i];
		i++;
	}
	message[i] = '\0';
} 

LatencyCheck::LatencyCheck() : code(LatencyCheck::Code::None) { ; }
LatencyCheck::LatencyCheck(LatencyCheck::Code _code) : code(_code) { ; }

Packet::Packet() : startByte(PACKET_START_BYTE), endByte(PACKET_END_BYTE), sender(THIS_DEVICE), 
	receiver(DEFAULT_RECEIVER_DEVICE), type(Packet::Type::Unknown) 
{ 
	memset(message, 0, 27); 
}

PacketHandler::PacketHandler() : m_startByteDetected(true), m_bufferIndex(0) { ; }

void PacketHandler::parseChar(char ch)
{
	if (m_startByteDetected)
	{
		m_buffer[m_bufferIndex] = ch;
		m_bufferIndex++;
		
		if (ch == PACKET_END_BYTE && m_bufferIndex == 32)
		{
			m_startByteDetected = false;
			Packet packet;
			auto size = sizeof (Packet);
			memcpy(&packet, m_buffer, 32);
			m_packets.push_back(packet);
		}
	}
	else
	{
		if (ch == PACKET_START_BYTE)
		{
			m_startByteDetected = true;
			memset(m_buffer, 0, sizeof (m_buffer));
			m_bufferIndex = 0;
			m_buffer[m_bufferIndex] = ch;
			m_bufferIndex++;
		}
	}
}

bool PacketHandler::packetAvailable()
{
	return !m_packets.empty();
}

Packet PacketHandler::getPacket()
{
	Packet result;
	
	if (!m_packets.empty())
	{
		result = m_packets.front();
		m_packets.pop_front();
	}
	return result;
}

Packet PacketHandler::createError(Error err, Device device)
{
	Packet result;
	
	result.receiver = device;
	result.type = Packet::Type::Error;
	result.error = err;
	return result;
}

Packet PacketHandler::createWarning(Warning warn, Device device)
{
	Packet result;
	
	result.receiver = device;
	result.type = Packet::Type::Warning;
	result.warning = warn;
	
	return result;
}

Packet PacketHandler::createMessage(const char* msg, Device device)
{
	Packet result;
	
	uint8_t i = 0;
	
	while (i < 26)
	{
		if (msg[i] == '\n' || msg[i] == '\r' || msg[i] == '\0')
			break;
		
		i++;
	}
	result.receiver = device;
	result.type = Packet::Type::Message;
	
	memcpy(result.message, msg, i);
	result.message[i] = '\0';
	return result;
}

Packet PacketHandler::createCommand(Command cmd, Device device)
{
	Packet result;
	
	result.receiver = device;
	result.type = Packet::Type::Command;
	result.command = cmd;
	return result;
}

#if defined(__XAVIER)

const std::unordered_map<Error::Code, std::string> __error_code_lookup_table = {
	{ Error::Code::LatchBatteryEmpty, "Latch battery is empty and requires imediate recharge." },
	{ Error::Code::LatchFailedToClose, "Latch failed to close." },
	{ Error::Code::LatchFailedToOpen, "Latch failed to open." },
	{ Error::Code::UnknownPacket, "Unknown packet received." },
	{ Error::Code::Other, "Undefined error occured." }
};

std::string errorMessage(Error::Code error_code)
{
	auto result = __error_code_lookup_table.find(error_code);

	if (result == __error_code_lookup_table.end())
		return "Unknown error code.";
	else
		return result->second;
}

const std::unordered_map<Warning::Code, std::string> __warning_code_lookup_table = {
	{ Warning::Code::LatchBatteryLow, "Latch battery is empty and requires imediate recharge." },
	{ Warning::Code::Other, "Undefined warning code." }
};

std::string warningMessage(Warning::Code warning_code)
{
	auto result = __warning_code_lookup_table.find(warning_code);

	if (result == __warning_code_lookup_table.end())
		return "Unknown warnign code.";
	else
		return result->second;
}

const std::unordered_map<Device, std::string> __device_lookup_table = {
	{ Device::Hook, "Hook" },
	{ Device::MainController, "UPLS controller" },
	{ Device::Xavier, "Xavier" }
};

std::string device(Device device)
{
	auto result = __device_lookup_table.find(device);

	if (result == __device_lookup_table.end())
		return "unknown device";
	else
		return result->second;
}

#endif // __XAVIER