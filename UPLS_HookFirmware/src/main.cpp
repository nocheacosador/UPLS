/*
 * Hook PCB Firmware.cpp
 *
 * Created: 8/27/2020 15:43:34
 * Author : lukas
 */ 

/*
* To configure AtTiny84 to work on 8MHz run this command on avrdude
 *(asuming UPBasp programmer is used):
*		avrdude -c usbasp -p t84 -P usb -U lfuse:w:0xe2:m
*/
#include "global_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <string.h>
#include "Packet.h"
#include "ADC.h"
#include "nRF24L01.h"
#include "RF24.h"
#include "Timer0.h"
#include "Latch.h"
#include "Battery.h"


uint8_t		past_retries[RETRY_BUFFER_SIZE];
uint8_t		last_retry_index = 0;
uint16_t	failed_send_attempts = 0;
uint32_t	last_status_report = 0;
uint32_t	last_battery_check = 0;

bool send_status_periodically = true;

Packet receiveBuffer;
HookInfo hookInfo;

RF24		radio(PB_0, PB_1);
Latch		latch(PA_1, DifferentialADC::Channel::ADC3_ADC2);
Battery		battery(SingleADC::Channel::ADC0, PA_7);
SingleADC	temp(SingleADC::Channel::TEMP, SingleADC::Reference::INT);

void answerLatencyCheckRequest();
void updateHookInfo(HookInfo& info);

void handleCommand(Command& command);
void handleLatencyCheck(LatencyCheck& latencyCheck);

void sendHookInfo(const HookInfo& info, const Device receiver = Device::Xavier);
void sendWarning(const Warning& warning, const Device receiver = Device::Xavier);
void sendError(const Error& error, const Device receiver = Device::Xavier);
void sendMessage(const char* message, const Device receiver = Device::Xavier);
void sendPacket(Packet& message);

void shutdown();

int main(void)
{
	init_timer0();
	memset(past_retries, 0, sizeof(past_retries));

	radio.begin();

	radio.setChannel(16);
	radio.setRetries(15, 15);
	radio.setPALevel(RF24_PA_MAX);
	radio.setDataRate(RF24_250KBPS);
	radio.setCRCLength(RF24_CRC_8);
	
	radio.openReadingPipe(1, addresses[0]);
	radio.startListening();

	while (1) 
    {
		// handle incoming commands if any
		if (radio.available())
		{
			radio.read(&receiveBuffer, sizeof(Packet));
			
			switch (receiveBuffer.type)
			{
			case Packet::Type::LatencyCheck:
				handleLatencyCheck(receiveBuffer.latencyCheck);
				break;
		
			case Packet::Type::Command:
				handleCommand(receiveBuffer.command);
				break;
		
			default:
				break;
			}
		}
		
		// this allows latch object to handle internal logic for closing, opening and retries without blocking
		Error latch_error;
		if (!latch.handle(&latch_error))
			sendError(latch_error);
		
		updateHookInfo(hookInfo);

		if (millis() - last_battery_check >= BATTERY_CHECK_PERIOD)
		{
			static uint16_t last_battery_voltage = 4200;
			static uint8_t	shutdown_counter;
			static bool		warning_sent = false;

			last_battery_check = millis();

			if (hookInfo.battery.voltage <= BATTERY_EMPTY_VOLTAGE && last_battery_voltage <= BATTERY_EMPTY_VOLTAGE 
				&& hookInfo.battery.state != Battery::State::Charging)
			{
				if (shutdown_counter++ >= BATTERY_EMPTY_TRESHOLD_COUNTER)
				{
					sendError(Error(Error::Code::LatchBatteryEmpty, "Bat empty. Shutting down..."));
					shutdown();
					shutdown_counter = 0;
					warning_sent = false;
				}
			}
			else if (hookInfo.battery.voltage <= BATTERY_WARNING_VOLTAGE && last_battery_voltage <= BATTERY_WARNING_VOLTAGE
				&& hookInfo.battery.state != Battery::State::Charging)
			{
				if (!warning_sent)
				{
					sendWarning(Warning(Warning::Code::LatchBatteryLow, "Low battery. Please recharge."));
					warning_sent = true;
				}

				shutdown_counter = 0;
			}
			else 
			{
				warning_sent = false;
				shutdown_counter = 0;
			}

			last_battery_voltage = hookInfo.battery.voltage;
		}

		if (send_status_periodically && millis() - last_status_report >= STATUS_REPORT_PERIOD)
		{
			last_status_report = millis();
			sendHookInfo(hookInfo);
		}
    }
}

void answerLatencyCheckRequest()
{
	Packet packet;

	packet.type = Packet::Type::LatencyCheck;
	packet.latencyCheck.code = LatencyCheck::Code::Answer;

	sendPacket(packet);
}

void updateHookInfo(HookInfo& info)
{	
	info.averageRetrie = 0.f;

	for (uint8_t i = 0; i < RETRY_BUFFER_SIZE; i++)
		info.averageRetrie += float(past_retries[i]);
	
	info.averageRetrie /= float(RETRY_BUFFER_SIZE);

	info.battery.state		= battery.getState();
	info.battery.voltage	= battery.getVoltage();
	info.latch.current		= uint16_t(latch.getCurrent() * 1000.f);
	info.latch.state		= latch.getStatus();
	info.latch.closePulseDuration = latch.getClosePulseDuration();
	info.latch.openPulseDuration  = latch.getOpenPulseDuration();
	info.lostMessages		= failed_send_attempts;
	info.mcuRuntime			= float(millis()) / 1000.f;
	info.temperature		= int16_t(float(temp.read()) * 8.33333f - 2156.66666f);
}

void handleCommand(Command& command)
{
	switch (command.code)
	{
	case Command::Code::StatusRequest:
		sendHookInfo(hookInfo);
		break;
		
	case Command::Code::LatchOpen:
		latch.open();
		break;
		
	case Command::Code::LatchClose:
		latch.close();
		break;
	
	case Command::Code::SetLatchOpenPulseDuration:
		latch.setOpenPulseDuration(command.pulseLength);
		break;

	case Command::Code::SetLatchClosePulseDuration:
		latch.setClosePulseDuration(command.pulseLength);
		break;

	case Command::Code::HookShutdown:
		sendMessage("Shutting down...");
		shutdown();
		break;

	default:
		break;
	}
}

void handleLatencyCheck(LatencyCheck& latencyCheck)
{
	if (latencyCheck.code == LatencyCheck::Code::Request)
		answerLatencyCheckRequest();
}

void sendHookInfo(const HookInfo& info, const Device receiver)
{
	Packet packet;

	packet.type = Packet::Type::HookInfo;
	packet.receiver = receiver;
	packet.hook = info;

	sendPacket(packet);
}

void sendWarning(const Warning& warning, const Device receiver)
{
	Packet packet;

	packet.type = Packet::Type::Warning;
	packet.receiver = receiver;
	packet.warning = warning;

	sendPacket(packet);
}

void sendError(const Error& error, const Device receiver)
{
	Packet packet;
	size_t size = sizeof(Packet);
	packet.type = Packet::Type::Error;
	packet.receiver = receiver;
	packet.error = error;

	sendPacket(packet);
}

void sendMessage(const char* message, const Device receiver)
{
	Packet packet;

	packet.type = Packet::Type::Message;
	packet.receiver = receiver;

	uint8_t i = 0;
	while (i < 26 && message[i] != '\0' && message[i] != '\n' && message[i] != '\r')
	{
		packet.message[i] = message[i];
		i++;
	}
	packet.message[i] = '\0';

	sendPacket(packet);
}

void sendPacket(Packet& packet)
{
	packet.sender = Device::Hook;

	radio.stopListening();
	radio.openWritingPipe(addresses[1]);

	bool success = radio.write(&packet, sizeof(Packet));

	radio.openReadingPipe(1, addresses[0]);
	radio.startListening();

	if (!success)
		failed_send_attempts++;
	else
	{
		past_retries[last_retry_index] = radio.getARC();
		last_retry_index = (last_retry_index + 1) % RETRY_BUFFER_SIZE;
	}
}

void shutdown()
{
	radio.powerDown();
	latch.turnOff();
	
	GIMSK  |= (1 << PCIE0);
	PCMSK0 |= (1 << PCINT7);

	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	
	power_all_disable();
	sleep_enable();
	
	sei();
	sleep_cpu();
	cli();
	
	GIMSK  &= ~(1 << PCIE0);
	PCMSK0 &= ~(1 << PCINT7);
	
	sleep_disable();
	power_all_enable();
	sei();

	latch.turnOn();
	radio.powerUp();
	radio.openReadingPipe(1, addresses[0]);
	radio.startListening();
}

ISR(PCINT0_vect)
{
	
}