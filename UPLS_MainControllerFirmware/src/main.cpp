#include <mbed.h>

#include "global_macros.h"
#include "packet.h"

#define UART_TX		PA_2
#define UART_RX		PA_3

PacketHandler  packetHandler;
UARTSerial 	   serial(UART_TX, UART_RX, 38400);
DigitalOut 	   led(PB_4);
Ticker 		   ticker;
// handle functions
void handleReceivedPacket(const Packet& packet);
void handleReceivedCommand(const Command& command);

void sendSomething();
void sendSun();

int main()
{
	//serial.baud(115200);
	led = 0;

	ticker.attach(&sendSomething, 1.0);
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
				auto error_packet = PacketHandler::createMessage("This packet isn't for me.", Device::Xavier);
				serial.write(&error_packet, sizeof(Packet));
			}
			else
			{
				handleReceivedPacket(packet);
			}
		}


		
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
	switch (command.code)
	{
	case Command::Code::LedsOn:
		led = 1;
		break;
	
	case Command::Code::LedsOff:
		led = 0;
		break;

	default:
		//serial.write("Unknown command!\n", 18);
		auto packet = PacketHandler::createError(Error(Error::Code::UnknownPacket, "Unknown command received."), Device::Xavier);
		serial.write(&packet, sizeof(Packet));
		break;
	}
}

void sendSomething()
{
	static uint8_t count;

	if (count == 0)
	{
		auto packet = PacketHandler::createError(Error(Error::Code::LatchFailedToOpen), Device::Xavier);
		serial.write(&packet, sizeof(Packet));
	}
	else if (count == 1)
	{
		auto packet = PacketHandler::createMessage("Hi, handsome :}", Device::Xavier);
		serial.write(&packet, sizeof(Packet));
	}
	else if (count == 2)
	{
		auto packet = PacketHandler::createMessage("Here's some sunshine 4 ya", Device::Xavier);
		serial.write(&packet, sizeof(Packet));

		sendSun();

	}
	count = (count + 1) % 3;
}

void sendSun()
{
	for (size_t i = 0; i < 9; i++)
	{
		auto packet = PacketHandler::createMessage(sun[i], Device::Xavier);
		serial.write(&packet, sizeof(Packet));
	}
}