#ifndef PACKET_H_
#define PACKET_H_

#if defined(__GNUC__) && !defined(__BINDINGS)
	#include <stdint-gcc.h>
	#define __NO_PADDING__  __attribute__((__packed__))
#else
	#include <stdint.h>
	#define __NO_PADDING__
	#if !defined(__BINDINGS)
		#warning There might be problems with padding.
	#endif	
#endif

//#if defined(__AVR)
//	#define __NO_PADDING__ 
//#else 
//	#define __NO_PADDING__ __attribute__((__packed__))
//#endif

#ifndef BINDINGS_API
	#define BINDINGS_API
#endif

#if !defined(__HOOK)
	#include "../Buffer/MyBuffer.h"
	#include <cstring>
#else
	#include <string.h>
#endif // !__HOOK

#define PACKET_START_BYTE '<'
#define PACKET_END_BYTE   '>'

/**
 * \brief Structure that holds information about UAV UPLS hook.
 */
struct BINDINGS_API __NO_PADDING__ HookInfo
{
	struct __NO_PADDING__ Battery 
	{
		enum class State : uint8_t
		{
			Unknown = 0,
			Charging,
			Discharging
		};
#if defined(__XAVIER)

		//void setVoltage(uint16_t _voltage);
		//void setState(State _state);
		float getVoltage() const;
		State getState() const;
		Battery(uint16_t _voltage = 0, State _state = State::Unknown);

	private:
#endif
		uint16_t voltage;
		State state;
	};

	struct __NO_PADDING__ Latch 
	{
		enum class State : uint8_t
		{
			Unknown = 0,
			Open,
			Closed,
			Opening,
			Closing
		};

#if defined(__XAVIER)
		void  setCurrent(uint16_t _current) { current = _current; }
		float getCurrent() const { return float(current) / 1000.f; }

		void  setState(State _state) { state = _state; }
		State getState() const { return state; }

		uint16_t getOpenPulseDuration() { return openPulseDuration; }
		uint16_t getClosePulseDuration() { return closePulseDuration; }

		Latch(State _state = State::Unknown, uint16_t _current = 0) 
			: state(_state), current(_current), closePulseDuration(0),
			openPulseDuration(0) { ; }

	private:
#endif // __XAVIER
		State state;
		uint16_t current;
		uint16_t closePulseDuration;
		uint16_t openPulseDuration;
	};

#if defined(__XAVIER)
	float getAverageRetrie() const { return averageRetrie; }
	//void  setAverageRetrie(float _averageRetrie) { averageRetrie = _averageRetrie}

	float getMCURuntime() const { return mcuRuntime; }
	//void  setMCURuntime(float _mcuRuntime) { mcuRuntime = _mcuRuntime; }

	uint16_t getlostMessages() const { return lostMessages; }

	float getTemperature() const { return float(temperature) / 10.f; }

	Battery getBatteryInfo() const { return battery; }

	Latch getLatchInfo() const { return latch; }

private:
#endif // __XAVIER
	float		averageRetrie;
	float		mcuRuntime;
	uint16_t	lostMessages;
	int16_t		temperature;
	Battery 	battery;
	Latch		latch;
	
public:
	HookInfo();
};

#if !defined(__HOOK)
struct BINDINGS_API __NO_PADDING__ LedInfo
{
	struct __NO_PADDING__ Led
	{
		enum class Mode : uint8_t
		{
			Unknown = 0,
			Normal,
			Soft,
			Pulsing
		};

		struct __NO_PADDING__ Settings
		{
# if defined(__XAVIER)
			Settings(uint8_t onValue = 255, uint8_t offValue = 0, uint16_t fadeInDuration = 500, 
				uint16_t fadeOutDuration = 500, uint16_t onDuration = 1000, 
				uint16_t offDuration = 1000) 
					: on_value(onValue), off_value(offValue),  
					on_duration(onDuration), off_duration(offDuration),
					fade_in_duration(fadeInDuration), fade_out_duration(fadeOutDuration) { ; }

			uint16_t getFadeInDuration() const { return fade_in_duration; }
			uint16_t getFadeOutDuration() const { return fade_out_duration; }
			uint16_t getOnDuration() const { return on_duration; }
			uint16_t getOffDuration() const { return off_duration; }
			uint8_t getOnValue() const { return on_value; }
			uint8_t getOffValue() const { return off_value; }
		private:
# endif // __XAVIER
			uint8_t on_value;
			uint8_t off_value;
			uint16_t on_duration;
			uint16_t off_duration;
			uint16_t fade_in_duration;
			uint16_t fade_out_duration;
		};
# if defined(__XAVIER)		
		Led() { ; }

		bool getEnabled() const { return enabled; }
		uint8_t getCurrentValue() const { return current_value; }
		Mode getMode() const { return mode; }
		Settings getSettings() const { return settings; }

	private:
# endif // __XAVIER
		bool     enabled;
		uint8_t  current_value;
		Mode	 mode;
		Settings settings;
	};

# if defined(__XAVIER)
	Led frontInfo() const { return front; }
	Led rearInfo() const  { return rear; }
private:
# endif // __XAVIER

	Led front;
	Led rear;

public:
	LedInfo();
	LedInfo(Led both) : front(both), rear(both) { ; }
	LedInfo(Led _front, Led _rear) : front(_front), rear(_rear) { ; }
};

struct BINDINGS_API __NO_PADDING__ LandingGearInfo
{
	struct __NO_PADDING__ Leg
	{
		enum class Status : uint8_t
		{
			Unknown = 0,
			Down,
			Up,
			InDownTransit,
			InUpTransit
		};
# if defined(__XAVIER)
		Leg() { ; }

		Status getStatus() const { return status; }
		uint8_t getValue() const { return value; }
		uint16_t getCurrent() const { return current; }

	private:
# endif // __XAVIER
		Status	 status;
		uint8_t  value;
		uint16_t current;
	};

# if defined(__XAVIER)
	Leg frontInfo() const { return front; }
	Leg rearInfo() const { return rear; }
private:
# endif // __XAVIER

	Leg front;
	Leg rear;

public:
	LandingGearInfo();
};

struct BINDINGS_API __NO_PADDING__ WinchInfo
{	
	enum class Status 
	{
		Unknown = 0,
		Lowering,
		GoingHome,
		Halted,
		Lowered,
		Home,
		Manual,
		Docking
	};

# if defined(__XAVIER)
	Status	 getStatus() const { return status; }
	float	 getPosition() const { return position; }
	float	 getTarget() const { return target; }
	uint16_t getCurrent() const { return current; }
private:
# endif // __XAVIER
	uint16_t current;
	float    position;
	float    target;
	Status 	 status;

public:
	WinchInfo();
};

struct BINDINGS_API __NO_PADDING__ MainControllerInfo
{
#if defined(__XAVIER)
	MainControllerInfo();

	float getUtilization() const;
	
private:
#endif // __XAVIER
	float utilization;
};

#endif // !__HOOK

struct BINDINGS_API __NO_PADDING__ Error
{
	enum Code : uint8_t
	{
		Other = 0,
		LatchFailedToClose,
		LatchFailedToOpen,
		LatchBatteryEmpty,
		UnknownPacket,
		UnknownReceiverDevice
	};

#if defined(__XAVIER)
	Code getCode() const { return code; }
	const char* getMessage() const { return message; }
private:
#endif // __XAVIER
	Code code;
	char message[26];

public:
	Error();
	Error(Code _code);
	Error(Code _code, const char* msg);
};

struct BINDINGS_API __NO_PADDING__ Warning
{
	enum class Code : uint8_t
	{
		Other = 0,
		LatchBatteryLow
	};

#if defined(__XAVIER)
	Code getCode() const { return code; }
	const char* getMessage() const { return message; }
private:
#endif // __XAVIER
	Code code;
	char message[26];

public:
	Warning();
	Warning(Code _code);
	Warning(Code _code, const char* msg);
};

struct __NO_PADDING__ LatencyCheck
{
	enum class Code : uint8_t
	{
		None = 0,
		Request,
		Answer
	};

#if defined(__XAVIER)
	Code getCode() { return code; }

private:
#endif // __XAVIER
	Code code;

public:
	LatencyCheck();
	LatencyCheck(Code _code);
};

enum class Device : uint8_t
{
	Unknown = 0,
	Xavier,
	Hook,
	MainController
};

#if defined(THIS_DEVICE)
	#if THIS_DEVICE == 1
		#undef THIS_DEVICE
		#define THIS_DEVICE		Device::Xavier
	#elif THIS_DEVICE == 2
		#undef THIS_DEVICE
		#define THIS_DEVICE		Device::Hook
	#elif THIS_DEVICE == 3
		#undef THIS_DEVICE
		#define THIS_DEVICE		Device::MainController
	#else
		#error THIS_DEVICE macro has invalid value. Valid values are: 1 - Xavier; 2 - Hook; 3 - Main Controller.
		#undef THIS_DEVICE
		#define THIS_DEVICE Device::Unknown
	#endif
#else
	#error THIS_DEVICE macro is not defined.
	#undef THIS_DEVICE
	#define THIS_DEVICE Device::Unknown
#endif // THIS_DEVICE

#if defined(DEFAULT_RECEIVER_DEVICE)
	#if DEFAULT_RECEIVER_DEVICE == 1
		#undef DEFAULT_RECEIVER_DEVICE
		#define DEFAULT_RECEIVER_DEVICE		Device::Xavier
	#elif DEFAULT_RECEIVER_DEVICE == 2
		#undef DEFAULT_RECEIVER_DEVICE
		#define DEFAULT_RECEIVER_DEVICE		Device::Hook
	#elif DEFAULT_RECEIVER_DEVICE == 3
		#undef DEFAULT_RECEIVER_DEVICE
		#define DEFAULT_RECEIVER_DEVICE		Device::MainController
	#else
		#undef DEFAULT_RECEIVER_DEVICE
		#error DEFAULT_RECEIVER_DEVICE macro has invalid value. Valid values are: 1 - Xavier; 2 - Hook; 3 - Main Controller.
		#define DEFAULT_RECEIVER_DEVICE Device::Unknown
	#endif
#else
	#undef DEFAULT_RECEIVER_DEVICE
	#error DEFAULT_RECEIVER_DEVICE macro is not defined.
	#define DEFAULT_RECEIVER_DEVICE Device::Unknown
#endif // THIS_DEVICE

/**
 * \brief Struct that is used to pass various commands and their parameters between devices.
 */
struct BINDINGS_API __NO_PADDING__ Command
{
	/**
	 * \brief Enum type containing command codes.
	 */
#if defined(__cpp_using_enum)
	enum class Code : uint8_t
#else
	enum Code : uint8_t
#endif
	{
		Unknown = 0,  					// do not change
		LatchClose = 1,					// do not change
		LatchOpen = 2,					// do not change
		SetLatchClosePulseDuration = 3,	// do not change
		SetLatchOpenPulseDuration = 4,	// do not change
		StatusRequest = 7,				// do not change
		HookShutdown = 12,				// do not change
		LedsEnableAll,
		LedsEnableFront,
		LedsEnableRear,
		LedsDisableAll,
		LedsDisableFront,
		LedsDisableRear,
		LedsOnAll,
		LedsOffAll,
		LedsOnRear,
		LedsOffRear,
		LedsOnFront,
		LedsOffFront,
		LedsSetSettingsAll,
		LedsSetSettingsRear,
		LedsSetSettingsFront,
		LedsSetModeAll,
		LedsSetModeRear,
		LedsSetModeFront,
		LandingGearExtract,
		LandingGearRetract,
		WinchManualUp,
		WinchManualDown,
		WinchLower,
		WinchHome,
		WinchHalt,
		WinchResume,
		WinchManualModeEnable,
		WinchManualModeDisable,
		StartCommunication,
		EndCommunication
	};

#if defined(__cpp_using_enum)
	using enum Code;
#endif

#if defined(__XAVIER)
	
	/**
	 * \brief Utility function for reading command code.
	 * \return Returns command code enum.
	 */
	Code getCode() { return code; }
	
	uint16_t getPulseLength() { return pulseLength; }

	Command& setCode(Code c) { code = c; return *this; }
	Command& setPulseLength(uint16_t value) { pulseLength = value; return *this; }
	Command& setLedMode(LedInfo::Led::Mode mode) { ledMode = mode; return *this; }
	Command& setLedSettings(LedInfo::Led::Settings settings) { ledSettings = settings; return *this; } 
	Command& setWinchManualSpeedAndDuration(float speed, float duration) { winch.speed = speed; winch.duration = duration; return *this;}
	Command& setWinchLowerDistance(float distance) { winch.lower_distance = distance; return *this; }
private:
#endif // __XAVIER

	Code code;

	union __NO_PADDING__
	{
		uint16_t pulseLength;
#if !defined(__HOOK)
		LedInfo::Led::Mode ledMode;
		LedInfo::Led::Settings ledSettings;
		struct {
			union {
				float duration;
				float lower_distance;
			};
			float speed;
		} winch;
#endif // __XAVIER
	};

public:
	/**  
	 * \brief Default constructor.
	 */
	Command();
	
	/**  
	 * \brief Overloaded constructor.
	 * Overloaded constructor for specifying command code.
	 * \param code Command code.
 	 */
	Command(Code code);
};


#if !defined(DOXYGEN_ONLY)
struct __NO_PADDING__ Packet
{
	enum class Type : uint8_t
	{
		Unknown = 0,
		Command,
		Message,
		Error,
		Warning,
		HookInfo,
		WinchInfo,
		LandingGearInfo,
		LedInfo,
		LatencyCheck,
		MainControllerInfo
	};
	
	char 	startByte;
	Device 	sender;
	Device 	receiver;
	Type 	type;

	union __NO_PADDING__ {
		char 		 	message[27];
		Command  	 	command;
		HookInfo 	 	hook;
#if !defined(__HOOK)
		LandingGearInfo		landingGear;
		LedInfo	 			led;
		WinchInfo  			winch;
		MainControllerInfo 	mainController;
#endif // !__HOOK
		Error		 	error;
		Warning		 	warning;
		LatencyCheck 	latencyCheck;
	};

	char endByte;

	Packet();
};

#if !defined(__HOOK)
typedef HookInfo::Battery	Battery;
typedef HookInfo::Latch		Latch;
typedef LedInfo::Led			Led;
typedef LandingGearInfo::Leg	Leg;


class PacketHandler
{
public:
	PacketHandler();

	void parseChar(char ch);

	bool packetAvailable();

	void pushPacket(const Packet& packet);

	Packet getPacket();

	static Packet createError(Error err, Device device = DEFAULT_RECEIVER_DEVICE);

	static Packet createWarning(Warning warn, Device device = DEFAULT_RECEIVER_DEVICE);

	static Packet createMessage(const char* msg, Device device = DEFAULT_RECEIVER_DEVICE);

	static Packet createCommand(Command cmd, Device device = DEFAULT_RECEIVER_DEVICE);

private:
	char 	m_buffer[32];
	uint8_t m_bufferIndex;
	bool 	m_startByteDetected;

	MyBuffer<Packet, 5> m_packets;
};
#endif // !__HOOK
#endif // DOXYGEN_ONLY

#if defined(__XAVIER)

#if !defined(DOXYGEN_ONLY)

#include <unordered_map>
#include <string>

extern const std::unordered_map<Error::Code, std::string> __error_code_lookup_table;
extern const std::unordered_map<Warning::Code, std::string> __warning_code_lookup_table;
extern const std::unordered_map<Device, std::string> __device_lookup_table;

#endif // !DOXYGEN_ONLY

std::string errorMessage(Error::Code error_code);
std::string warningMessage(Warning::Code warning_code);
std::string device(Device device);

#endif // __XAVIER

#endif // PACKET_H_