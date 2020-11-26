#ifndef MESSAGES_H_
#define MESSAGES_H_

#include <stdint.h>

struct  Command
{
	enum Code : uint8_t
	{
		NONE = 0,
		LATCH_OPEN,
		LATCH_CLOSE,
		SET_LATCH_CLOSE_PULSE,
		SET_LATCH_OPEN_PULSE,
		STATUS_REQUEST,
		SHUTDOWN
	} code;

	uint16_t pulseLength;

	Command() : code(NONE), pulseLength(0) { ; }
	Command(Code _code, uint16_t _pulseLength = 0) : code(_code), pulseLength(_pulseLength) { ; }
};

struct HookStatus
{
	uint8_t		latchState;
	uint16_t	latchCurrent;
	float		averageRetries;
	float		mcuRuntime;
	uint16_t	lostMessages;
	int16_t		temperature;
	uint16_t	batteryVoltage;
	uint8_t		batteryState;
};

struct Error
{
	enum Code : uint8_t
	{
		NONE = 0,
		LACTH_CLOSE_FAIL,
		LACTH_OPEN_FAIL,
		BATTERY_EMPTY
	} code;

	char message[30];

	Error() : code(NONE), message("") { ; }
	Error(Code _code) : code(_code), message("") { ; }
	Error(Code _code, const char* msg) : code(_code)
	{
		uint8_t i = 0;
		while (i < 30 && msg[i] != '\n' && msg[i] != '\0' && msg[i] != '\r')
		{
			message[i] = msg[i];
			i++;
		}
		message[i] = '\0';
	}
};

struct Warning
{
	enum Code : uint8_t
	{
		NONE = 0,
		BATTERY_LOW
	} code;

	char message[30];
	
	Warning() : code(NONE), message("") { ; }
	Warning(Code _code) : code(_code), message("") { ; }
	Warning(Code _code, const char* msg) : code(_code)
	{
		uint8_t i = 0;
		while (i < 30 && msg[i] != '\n' && msg[i] != '\0' && msg[i] != '\r')
		{
			message[i] = msg[i];
			i++;
		}
		message[i] = '\0';
	}
};

struct LatencyCheck
{
	enum Code : uint8_t
	{
		NONE = 0,
		REQUUEST,
		ANSWER
	} code;

	LatencyCheck() : code(NONE) { ; }
	LatencyCheck(Code _code) : code(_code) { ; }
};

union Package
{
	char str[32];
	
	enum Type : uint8_t
	{
		LATENCY_CHECK  = 'L',
		COMMAND		   = 'C',
		STATUS		   = 'S',
		MESSAGE		   = 'M',
		ERROR		   = 'E',
		WARNING        = 'W'
	};

	struct Payload
	{
		Type type;
		
		union {
			// Command
			Command  	 command;
			HookStatus 	 status;
			Error		 error;
			Warning		 warning;
			LatencyCheck latencyCheck;
			char message[31];
		};
	} payload;

	Package() { ; }
};

#endif /* MESSAGES_H_ */