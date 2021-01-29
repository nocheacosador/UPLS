#pragma GCC diagnostic ignored "-Wreorder"

#include <mbed.h>

#define TEST_SPACE
#if !defined(TEST_SPACE)

#include "global_macros.h"
#include "packet.h"
#include "LoopController.h"
#include "LedDriver.h"
#include "Winch.h"
#include "LandingGear.h"
#include "RF24.h"

PacketHandler  packetHandler;
Timer timer;

LoopController loopController(1000.f);

UARTSerial 	serial(UART_TX, UART_RX, 115200);
LedDriver 	led_rear(LEDS_REAR);
LedDriver	led_front(LEDS_FRONT);
Winch 		winch;
RF24		radio(RF24_MOSI, RF24_MISO, RF24_SCK, RF24_CSN, RF24_CE);
LandingGear landing_gear;

const uint8_t addresses[2][6] = { "10000", "20000" };
uint32_t failed_send_packets = 0;

void led_init();
void radio_init();
void landing_gear_init();

void wait_for_connection();

// handle functions
void handleReceivedPacket(const Packet& packet);
void handleReceivedCommand(const Command& command);

void sendWinchInfo();
void sendLandingGearInfo();
void sendLedInfo();
void sendMainControllerInfo();

void sendInfoPackets();

forceinline void sendToXavier(Packet& packet)
{
	serial.write(&packet, sizeof(Packet));
}

forceinline void sendToHook(Packet& packet)
{
	radio.stopListening();
	radio.openWritingPipe(addresses[0]);
	
	if (!radio.write(&packet, sizeof(Packet)))
		failed_send_packets++;

	radio.openReadingPipe(1, addresses[1]);
	radio.startListening();
}

int main()
{
	timer.start();

	led_init();
	radio_init();
	landing_gear_init();
	winch.enable(true);
	winch.enableManual(true);

	//wait_for_connection();

	while (1) 
	{
		while (serial.readable())
		{
			char ch;
			serial.read(&ch, 1);
			
			packetHandler.parseChar(ch);
		}

		if (radio.available())
		{
			Packet packet;
			radio.read(&packet, sizeof(Packet));
			packetHandler.pushPacket(packet);
		}

		while (packetHandler.packetAvailable())
		{
			auto packet = packetHandler.getPacket();

			if (packet.receiver != THIS_DEVICE)
			{
				// redirect packet
				switch (packet.receiver)
				{
				case Device::Xavier:
					sendToXavier(packet);
					break;

				case Device::Hook:
					sendToHook(packet);
					break;

				default:
					auto error_packet = PacketHandler::createError(Error(Error::Code::UnknownReceiverDevice), Device::Xavier);
					sendToXavier(error_packet);
					break;
				}
			}
			else
			{
				handleReceivedPacket(packet);
			}
		}

		sendInfoPackets();
		loopController.handle();
	}
}

void led_init()
{
	led_front.mode(LedDriver::Mode::Soft);
	led_front.settings({ 200, 0, 1000, 1000, 1000, 1000 });
	led_front.enable(false);

	led_rear.mode(LedDriver::Mode::Soft);
	led_rear.settings({ 200, 0, 1000, 1000, 1000, 1000 });
	led_rear.enable(false);
}

void radio_init()
{
	radio.begin();
	radio.setChannel(16);
	radio.setRetries(15, 15);
	radio.setPALevel(RF24_PA_MAX);
	radio.setDataRate(RF24_250KBPS);
	radio.setCRCLength(RF24_CRC_8);
	radio.setAutoAck(true);
	radio.openReadingPipe(1, addresses[1]);
	radio.startListening();
}

void landing_gear_init()
{
	landing_gear.front.enable(true);
	landing_gear.rear.enable(false);
}

void wait_for_connection()
{
	while (1)
	{
		while (serial.readable())
		{
			char ch;
			serial.read(&ch, 1);	
			packetHandler.parseChar(ch);
		}

		if (packetHandler.packetAvailable())
		{
			auto packet = packetHandler.getPacket();

			if (packet.type == Packet::Type::Command && packet.sender == Device::Xavier 
				&& packet.command.code == Command::StartCommunication)
			{
				auto msg = PacketHandler::createMessage("StartCom command received", Device::Xavier);
				sendToXavier(msg);
				break;
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
		auto packet = PacketHandler::createError(Error(Error::Code::UnknownPacket, "Unknown packet received."), Device::Xavier);
		sendToXavier(packet);
		break;
	}
}

void handleReceivedCommand(const Command& command)
{
	Packet packet;

	switch (command.code)
	{
	case Command::LedsEnableAll:
		led_front.enable(true);
		led_rear.enable(true);
		break;

	case Command::LedsEnableFront:
		led_front.enable(true);
		break;

	case Command::LedsEnableRear:
		led_rear.enable(true);
		break;

	case Command::LedsDisableAll:
		led_front.enable(false);
		led_rear.enable(false);
		break;

	case Command::LedsDisableFront:
		led_front.enable(false);
		break;

	case Command::LedsDisableRear:
		led_rear.enable(false);
		break;

	case Command::LedsOnAll:
		led_front.turnOn();
		led_rear.turnOn();
		break;

	case Command::LedsOffAll:
		led_front.turnOff();
		led_rear.turnOff();
		break;

	case Command::LedsOnRear:
		led_rear.turnOn();
		break;

	case Command::LedsOffRear:
		led_rear.turnOff();
		break;

	case Command::LedsOnFront:
		led_front.turnOn();
		break;

	case Command::LedsOffFront:
		led_front.turnOff();
		break;

	case Command::LedsSetSettingsAll:
		led_front.settings(command.ledSettings);
		led_rear.settings(command.ledSettings);
		break;

	case Command::LedsSetSettingsRear:
		led_rear.settings(command.ledSettings);
		break;

	case Command::LedsSetSettingsFront:
		led_front.settings(command.ledSettings);
		break;

	case Command::LedsSetModeAll:
		led_front.mode(command.ledMode);
		led_rear.mode(command.ledMode);
		break;
	
	case Command::LedsSetModeFront:
		led_front.mode(command.ledMode);
		break;

	case Command::LedsSetModeRear:
		led_rear.mode(command.ledMode);
		break;

	case Command::LandingGearExtract:
		landing_gear.extract();
		break;

	case Command::LandingGearRetract:
		landing_gear.retract();
		break;

	case Command::WinchLower:
		winch.lower(command.winch.lower_distance);
		break;

	case Command::WinchHome:
		winch.returnHome();
		break;

	case Command::WinchManualUp:
		winch.setManualUpSpeed(command.winch.speed, command.winch.duration);
		break;

	case Command::WinchManualDown:
		winch.setManualDownSpeed(command.winch.speed, command.winch.duration);
		break;

	case Command::WinchHalt:
		winch.halt();
		break;
	
	case Command::WinchResume:
		winch.resume();
		break;

	case Command::WinchManualModeEnable:
		winch.enableManual(true);
		break;

	case Command::WinchManualModeDisable:
		winch.enableManual(false);
		break;

	default:
		packet = PacketHandler::createError(Error(Error::Code::UnknownPacket, "Unknown command received."), Device::Xavier);
		sendToXavier(packet);
		break;
	}
}

void sendWinchInfo()
{
	Packet packet;
	
	packet.receiver = Device::Xavier;
	packet.type = Packet::Type::WinchInfo;

	packet.winch.current = winch.getCurrent();
	packet.winch.position = winch.getPosition();
	packet.winch.status = winch.getStatus();
	packet.winch.target = winch.getTarget();

	sendToXavier(packet);
}

void sendLandingGearInfo()
{
	Packet packet;
	
	packet.receiver = Device::Xavier;
	packet.type = Packet::Type::LandingGearInfo;

	packet.landingGear.front.current = landing_gear.front.getCurrent();
	packet.landingGear.front.status = landing_gear.front.getStatus();
	packet.landingGear.front.value = landing_gear.front.getValue();

	packet.landingGear.rear.current = landing_gear.rear.getCurrent();
	packet.landingGear.rear.status = landing_gear.rear.getStatus();
	packet.landingGear.rear.value = landing_gear.rear.getValue();

	sendToXavier(packet);
}

void sendLedInfo()
{
	Packet packet;
	
	packet.receiver = Device::Xavier;
	packet.type = Packet::Type::LedInfo;

	packet.led.front.current_value = led_front.value();
	auto mode = led_front.getMode();
	packet.led.front.mode = static_cast<LedInfo::Led::Mode>(mode);
	packet.led.front.enabled = led_front.isEnabled();
	auto settings = led_front.settings();
	packet.led.front.settings.on_value = settings.on_value;
	packet.led.front.settings.off_value = settings.off_value;
	packet.led.front.settings.on_duration = settings.on_duration;
	packet.led.front.settings.off_duration = settings.off_duration;
	packet.led.front.settings.fade_in_duration = settings.fade_in_duration;
	packet.led.front.settings.fade_out_duration = settings.fade_out_duration;

	packet.led.rear.current_value = led_rear.value();
	mode = led_rear.getMode();
	packet.led.rear.mode = static_cast<LedInfo::Led::Mode>(mode);
	packet.led.rear.enabled = led_rear.isEnabled();
	settings = led_rear.settings();
	packet.led.rear.settings.on_value = settings.on_value;
	packet.led.rear.settings.off_value = settings.off_value;
	packet.led.rear.settings.on_duration = settings.on_duration;
	packet.led.rear.settings.off_duration = settings.off_duration;
	packet.led.rear.settings.fade_in_duration = settings.fade_in_duration;
	packet.led.rear.settings.fade_out_duration = settings.fade_out_duration;
	
	sendToXavier(packet);
}

void sendMainControllerInfo()
{
	Packet packet;
	
	packet.receiver = Device::Xavier;
	packet.type = Packet::Type::MainControllerInfo;

	packet.mainController.utilization = loopController.getUtilization();

	sendToXavier(packet);
}

void sendInfoPackets()
{
	static int lastLed = 0;
	static int lastLandingGear = 0;
	static int lastWinch = 0;
	static int lastMainController = 0;

	int now = timer.read_ms();

	if (now - lastLed >= 200)
	{
		sendLedInfo();
		lastLed = now;
	}
	else if (now - lastLandingGear >= 200)
	{
		sendLandingGearInfo();
		lastLandingGear = now;
	}
	else if (now - lastWinch >= 200)
	{
		sendWinchInfo();
		lastWinch = now;
	}
	else if (now - lastMainController >= 50)
	{
		sendMainControllerInfo();
		lastMainController = now;
	}
}
#else
// TEST SPACE

#include "global_macros.h"

#include <Serial.h>
#include "Extruder.h"

#include <string>

using namespace mbed;

Serial serial(UART_TX, UART_RX, 115200);
Extruder extruder(EXTRUDER_DIR, EXTRUDER_PWM);

char buf[100];
int buf_index = 0;

int main()
{	
	serial.printf("Extruder test.\n");

	while (1)
	{
		buf_index = 0;
		while (true)
		{
			if (serial.readable())
			{
				char c = serial.getc();
				if (c == '\n' || c == '\r') break;
				buf[buf_index++] = c;
			}
		}
		buf[buf_index++] = '\0';

		char c_str[50];
		float speed = 1.f;

		auto args_read = sscanf(buf, "%s %f", c_str, &speed);

		if (args_read == 0)
		{
			extruder.stop();
			serial.printf("No args read.\n");
			continue;
		}

		std::string str(c_str);

		if (str == "extrude")
		{
			if (args_read == 2)
			{
				if (speed > 1.f) speed = 1.f;
				else if (speed < 0.f) speed = 0.f;
			}

			extruder.extrude(speed);
			serial.printf("Extruding... speed = %f\n", speed);
		}
		else if (str == "retract")
		{
			if (args_read == 2)
			{
				if (speed > 1.f) speed = 1.f;
				else if (speed < 0.f) speed = 0.f;
			}
			extruder.retract(speed);
			serial.printf("Retracting... speed = %f\n", speed);
		}
		else if (str == "stop")
		{
			extruder.stop();
			serial.printf("Stopped.\n");
		}
		else
		{
			extruder.stop();
			serial.printf("Unknown command: \"%s\"\n", str.c_str());
		}
	}
}

#endif // TEST_SPACE