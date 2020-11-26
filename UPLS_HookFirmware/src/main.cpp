/*
 * Hook PCB Firmware.cpp
 *
 * Created: 8/27/2020 15:43:34
 * Author : lukas
 */ 

/*
* To configure AtTiny84 to work on 8MHz run this command on avrdude:
*		-c usbasp -p t84 -P usb -U lfuse:w:0xe2:m
*/

#include "definitions.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <string.h>
#include "messages.h"
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

Package receiveBuffer;
HookStatus hookStatus;

RF24		radio(PB_0, PB_1);
Latch		latch(PA_1, DifferentialADC::Channel::ADC3_ADC2);
Battery		battery(SingleADC::Channel::ADC0, PA_7);
SingleADC	temp(SingleADC::Channel::TEMP, SingleADC::Reference::INT);

void answerLatencyCheckRequest();
void updateStatus(HookStatus& status);

void handleCommand(Command& command);
void handleLatencyCheck(LatencyCheck& latencyCheck);

void sendStatus(const HookStatus& status);
void sendWarning(const Warning& warning);
void sendError(const Error& error);
void sendMessage(const char* message);
void sendPackage(Package& message);

void shutdown();

int main(void)
{
	init_timer0();
	memset(past_retries, 0, sizeof(past_retries));

	radio.begin();

	radio.setChannel(16);
	radio.setRetries(15, 15);
	radio.setPALevel(RF24_PA_MIN);
	radio.setDataRate(RF24_250KBPS);
	radio.setCRCLength(RF24_CRC_8);
	
	radio.openReadingPipe(1, addresses[0]);
	radio.startListening();

	while (1) 
    {
		// handle incoming commands if any
		if (radio.available())
		{
			radio.read(&receiveBuffer, sizeof(Package));
			
			switch (receiveBuffer.payload.type)
			{
			case Package::Type::LATENCY_CHECK:
				handleLatencyCheck(receiveBuffer.payload.latencyCheck);
				break;
		
			case Package::Type::COMMAND:
				handleCommand(receiveBuffer.payload.command);
				break;
		
			default:
				break;
			}
		}
		
		// this allows latch object to handle internal logic for closing, opening and retries without blocking
		latch.handle();
		
		updateStatus(hookStatus);

		if (millis() - last_battery_check >= BATTERY_CHECK_PERIOD)
		{
			static uint16_t last_battery_voltage = 4200;
			static uint8_t	shutdown_counter;
			static bool		warning_sent = false;

			last_battery_check = millis();

			if (hookStatus.batteryVoltage <= BATTERY_EMPTY_VOLTAGE && last_battery_voltage <= BATTERY_EMPTY_VOLTAGE 
				&& hookStatus.batteryState != Battery::CHARGING)
			{
				if (shutdown_counter++ >= BATTERY_EMPTY_TRESHOLD_COUNTER)
				{
					sendError(Error(Error::Code::BATTERY_EMPTY, "Battery is empty. Shutting down..."));
					shutdown();
					shutdown_counter = 0;
					warning_sent = false;
				}
			}
			else if (hookStatus.batteryVoltage <= BATTERY_WARNING_VOLTAGE && last_battery_voltage <= BATTERY_WARNING_VOLTAGE
				&& hookStatus.batteryState != Battery::CHARGING)
			{
				if (!warning_sent)
				{
					sendWarning(Warning(Warning::Code::BATTERY_LOW, "Low battery. Please recharge."));
					warning_sent = true;
				}

				shutdown_counter = 0;
			}
			else 
			{
				warning_sent = false;
				shutdown_counter = 0;
			}

			last_battery_voltage = hookStatus.batteryVoltage;
		}

		if (send_status_periodically && millis() - last_status_report >= STATUS_REPORT_PERIOD)
		{
			last_status_report = millis();
			sendStatus(hookStatus);
		}
    }
}

void answerLatencyCheckRequest()
{
	Package package;
	
	package.payload.type = Package::LATENCY_CHECK;
	package.payload.latencyCheck.code = LatencyCheck::Code::ANSWER;

	sendPackage(package);
}

void updateStatus(HookStatus& status)
{	
	status.averageRetries = 0.f;

	for (uint8_t i = 0; i < RETRY_BUFFER_SIZE; i++)
	status.averageRetries += float(past_retries[i]);
	
	status.averageRetries /= float(RETRY_BUFFER_SIZE);

	status.batteryState		= battery.getState();
	status.batteryVoltage	= battery.getVoltage();
	status.latchCurrent		= uint16_t(latch.getCurrent() * 1000.f);
	status.latchState		= latch.getStatus();
	status.lostMessages		= failed_send_attempts;
	status.mcuRuntime		= float(millis()) / 1000.f;
	status.temperature		= int16_t(float(temp.read()) * 8.33333f - 2156.66666f);
}

void handleCommand(Command& command)
{
	switch (command.code)
	{
	case Command::Code::STATUS_REQUEST:
		sendStatus(hookStatus);
		break;
		
	case Command::Code::LATCH_OPEN:
		latch.open();
		sendMessage("Opening");
		break;
		
	case Command::Code::LATCH_CLOSE:
		latch.close();
		sendMessage("Closing");
		break;
	
	case Command::Code::SET_LATCH_OPEN_PULSE:
		latch.setOpenPulseDuration(command.pulseLength);
		break;

	case Command::Code::SET_LATCH_CLOSE_PULSE:
		latch.setClosePulseDuration(command.pulseLength);
		break;

	case Command::Code::SHUTDOWN:
		sendMessage("Shutting down...");
		shutdown();
		break;

	default:
		break;
	}
}

void handleLatencyCheck(LatencyCheck& latencyCheck)
{
	if (latencyCheck.code == LatencyCheck::Code::REQUUEST)
		answerLatencyCheckRequest();
}

void sendStatus(const HookStatus& status)
{
	Package package;
	
	package.payload.type = Package::Type::STATUS;
	package.payload.status = status;

	sendPackage(package);
}

void sendWarning(const Warning& warning)
{
	Package package;

	package.payload.type = Package::Type::WARNING;
	package.payload.warning = warning;

	sendPackage(package);
}

void sendError(const Error& error)
{
	Package package;

	package.payload.type = Package::Type::ERROR;
	package.payload.error = error;

	sendPackage(package);
}

void sendMessage(const char* message)
{
	Package package;

	package.payload.type = Package::Type::MESSAGE;
	
	uint8_t i = 0;
	while (i < 30 && message[i] != '\0' && message[i] != '\n' && message[i] != '\r')
	{
		package.payload.message[i] = message[i];
		i++;
	}
	package.payload.message[i] = '\0';

	sendPackage(package);
}

void sendPackage(Package& package)
{
	radio.stopListening();
	radio.openWritingPipe(addresses[1]);

	bool success = radio.write(&package, sizeof(Package));

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