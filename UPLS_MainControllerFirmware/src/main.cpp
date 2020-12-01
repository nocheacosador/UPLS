#include <mbed.h>

#include "global_macros.h"
#include "packet.h"
#include "LoopController.h"


#define UART_TX		PA_2
#define UART_RX		PA_3

PacketHandler  packetHandler;
UARTSerial 	   serial(UART_TX, UART_RX, 38400);
DigitalOut 	   led(PB_4);

Ticker 		   tick_HookInfo;
Ticker 		   tick_LandingGearInfo;
Ticker 		   tick_WinchInfo;

// handle functions
void handleReceivedPacket(const Packet& packet);
void handleReceivedCommand(const Command& command);

void sendHookInfo();
void sendWinchInfo();
void sendLandingGearInfo();

void sendSun();

int main()
{
	LoopController loop(1000.f);
	led = 0;

	tick_HookInfo.attach(&sendHookInfo, 0.1);
	tick_LandingGearInfo.attach(&sendWinchInfo, 0.4);
	tick_WinchInfo.attach(&sendLandingGearInfo, 1.0);
	// put your setup code here, to run once:
	
	while (1) 
	{
		while (serial.readable())
		{
			char ch;
			serial.read(&ch, 1);
			
			packetHandler.parseChar(ch);
		}

		while (packetHandler.packetAvailable())
		{
			serial.write("Packet received.\n", 19);
			
			auto packet = packetHandler.getPacket();

			if (packet.receiver != THIS_DEVICE)
			{
				// redirect packet
				auto message_packet = PacketHandler::createMessage("This packet isn't for me.", Device::Xavier);
				serial.write(&message_packet, sizeof(Packet));
			}
			else
			{
				handleReceivedPacket(packet);
			}
		}


		loop.handle();
	}
}

void handleReceivedPacket(const Packet& packet)
{
	switch (packet.type)
	{
	case Packet::Type::Command:
		handleReceivedCommand(packet.command);
		break;

	default:
		//serial.write("Unknown packet!\n", 18);
		auto packet = PacketHandler::createError(Error(Error::Code::UnknownPacket, "Unknown packet received."), Device::Xavier);
		serial.write(&packet, sizeof(Packet));
		break;
	}
}

void handleReceivedCommand(const Command& command)
{
	Packet packet;

	switch (command.code)
	{
	case Command::Code::LedsOn:
		packet = PacketHandler::createMessage("Led on.", Device::Xavier);
		serial.write(&packet, sizeof(Packet));
		//led = 1;
		break;
	
	case Command::Code::LedsOff:
		packet = PacketHandler::createMessage("Led off.", Device::Xavier);
		serial.write(&packet, sizeof(Packet));
		//led = 0;
		break;

	default:
		//serial.write("Unknown command!\n", 18);
		packet = PacketHandler::createError(Error(Error::Code::UnknownPacket, "Unknown command received."), Device::Xavier);
		serial.write(&packet, sizeof(Packet));
		break;
	}
}

void sendHookInfo()
{
	static Packet packet;

	packet.receiver = Device::Xavier;
	packet.type = Packet::Type::HookInfo;

	packet.hook.averageRetrie+= 0.01f;
	packet.hook.battery.state = Battery::State::Discharging;
	packet.hook.battery.voltage = 4200;
	packet.hook.latch.state = Latch::State::Open;
	packet.hook.latch.current += uint16_t(1000.f * (sin(packet.hook.averageRetrie) + 1.f));
	packet.hook.lostMessages += 10;
	packet.hook.mcuRuntime += 0.1f;
	packet.hook.temperature = 210;

	serial.write(&packet, sizeof(Packet));
}

void sendWinchInfo()
{
	static Packet packet;
	
	packet.receiver = Device::Xavier;
	packet.type = Packet::Type::WinchInfo;

	packet.winch.current = 1234;
	packet.winch.position = -5.9f;
	packet.winch.status = WinchInfo::Status::Lowered;

	serial.write(&packet, sizeof(Packet));
}

void sendLandingGearInfo()
{
	static Packet packet;
	
	packet.receiver = Device::Xavier;
	packet.type = Packet::Type::LandingGearInfo;

	packet.landingGear.front.current = 4321;
	packet.landingGear.front.status = LandingGearInfo::Leg::Status::Opening;
	packet.landingGear.front.value = 255;

	packet.landingGear.rear.current = 5468;
	packet.landingGear.rear.status = LandingGearInfo::Leg::Status::Closed;
	packet.landingGear.rear.value = 128;

	serial.write(&packet, sizeof(Packet));
}
