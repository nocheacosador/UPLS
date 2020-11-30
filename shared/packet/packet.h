#ifndef PACKET_H_
#define PACKET_H_

#if defined(__GNUC__) && !defined(__BINDINGS)
	#include <stdint-gcc.h>
#else
	#include <stdint.h>
#endif

#if defined(__AVR)
	#define __NO_PADDING__ 
#else 
	#define __NO_PADDING__ __attribute__((__packed__))
#endif

#ifndef BINDINGS_API
	#define BINDINGS_API
#endif

#include <list>
#include <cstring>

#define PACKET_START_BYTE '<'
#define PACKET_END_BYTE   '>'

/**
 * \brief Struct that is used to pass various commands and their parameters between devices.
 */
struct BINDINGS_API __NO_PADDING__ Command
{
	/**
	 * \brief Enum type containing command codes.
	 */
	enum class Code : uint8_t
	{
		Unknown = 0,
		OpenLatch,
		CloseLatch,
		SetLatchClosePulseDuration,
		SetLatchOpenPulseDuration,
		StatusRequest,
		LedsOn,
		LedsOff,
		LatchShutdown
	};

#if defined(__XAVIER)
	
	/**
	 * \brief Utility function for reading command code.
	 * \return Returns command code enum.
	 */
	Code getCode() { return code; }
	
# if !defined(DOXYGEN_ONLY)
	uint16_t getPulseLength() { return pulseLength; }
	void setPulseLength(uint16_t value) { pulseLength = value; };
# endif // !DOXYGEN_ONLY

private:
#endif // __XAVIER

	Code code;
	uint16_t pulseLength;

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

		//void 	 setVoltage(uint16_t _voltage) { voltage = _voltage; }
		float getVoltage() const { return float(voltage) / 1000.f; }

		//void  setState(State _state) { state = _state; }
		State getState() const { return state; }

		Battery(uint16_t _voltage = 0, State _state = State::Unknown) : voltage(_voltage), state(_state) { ; }

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

		Latch(State _state = State::Unknown, uint16_t _current = 0) : state(_state), current(_current) { ; }

	private:
#endif // __XAVIER
		State state;
		uint16_t current;
	};

#if defined(__XAVIER)
	float getAverageRetrie() const { return averageRetrie; }
	//void  setAverageRetrie(float _averageRetrie) { averageRetrie = _averageRetrie}

	float getMCURuntime() const { return mcuRuntime; }
	//void  setMCURuntime(float _mcuRuntime) { mcuRuntime = _mcuRuntime; }

	uint16_t getlostMessages() const { return mcuRuntime; }

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
			Pulsing,
			FadeInOut,
			Blinking
		};

		struct __NO_PADDING__ Pulsing 
		{
#if defined(__XAVIER)
			Pulsing(uint16_t _fadeInDuration = 900, uint16_t _fadeOutDuration = 900, uint16_t _maxValueDuration = 100, 
				uint16_t _minValueDuration = 100, uint8_t _maxValue = 255, uint8_t _minValue = 0) : fadeInDuration(_fadeInDuration),
				fadeOutDuration(_fadeOutDuration), maxValueDuration(_maxValueDuration), minValueDuration(_minValueDuration), 
				maxValue(_maxValue), minValue(_minValue) { ; }

			uint16_t getFadeInDuration() const { return fadeInDuration; }
			uint16_t getFadeOutDuration() const { return fadeOutDuration; }
			uint16_t getMaxValueDuration() const { return maxValueDuration; }
			uint16_t getMinValueDuration() const { return minValueDuration; }
			uint8_t getMaxValue() const { return maxValue; }
			uint8_t getMinValue() const { return minValue; }
		private:
#endif // __XAVIER
			uint16_t fadeInDuration;	// in ms
			uint16_t fadeOutDuration;	// in ms
			uint16_t maxValueDuration;	// in ms
			uint16_t minValueDuration;	// in ms
			uint8_t  maxValue;
			uint8_t  minValue;
		};

		struct __NO_PADDING__ Blinking 
		{
#if defined(__XAVIER)
		Blinking(uint16_t _onDuration = 1000, uint16_t _offDuration = 1000) : onDuration(_onDuration), offDuration(_offDuration) { ; }
		
		uint16_t getOnDuration() const { return onDuration; }
		uint16_t getOffDuration() const { return offDuration; }
		
		private:
#endif // __XAVIER
			uint16_t onDuration;	// in ms
			uint16_t offDuration;	// in ms
		};

		struct __NO_PADDING__ Normal
		{
#if defined(__XAVIER)
		Normal(uint8_t _brightness = 255) : brightness(_brightness) { ; }

		uint8_t getBrightness() const { return brightness; }

		private:
#endif // __XAVIER
			uint8_t brightness;
		};

		struct __NO_PADDING__ FadeInFadeOut 
		{
#if defined(__XAVIER)
			FadeInFadeOut(uint8_t _brightness = 255, uint16_t _fadeInDuration = 1000, uint16_t _fadeOutDuration = 1000)
				: fadeInDuration(_fadeInDuration), fadeOutDuration(_fadeOutDuration), brightness(_brightness) { ; }

			uint16_t getFadeInDuration() const { return fadeInDuration; }
			uint16_t getFadeOutDuration() const { return fadeOutDuration; }
			uint8_t  getBrightness() const { return brightness; }

		private:
#endif // __XAVIER
			uint16_t fadeInDuration;	// in ms
			uint16_t fadeOutDuration;	// in ms
			uint8_t  brightness;
		};

#if defined(__XAVIER)
		
		Led() { memset(this, 0, sizeof(Led)); } 
		Led(Pulsing _pulsing) : pulsing(_pulsing), mode(Mode::Pulsing) { ; }
		Led(Blinking _blinking) : blinking(_blinking), mode(Mode::Blinking) { ; }
		Led(Normal _normal) : normal(_normal), mode(Mode::Normal) { ; }
		Led(FadeInFadeOut _fadeInOut) : fadeInOut(_fadeInOut), mode(Mode::FadeInOut) { ; }

		bool getEnabled() const { return enabled; }
		uint8_t getCurrentValue() const { return current_value; }
		Mode getMode() const { return mode; }
		Pulsing	getPulsingSettings() const { return pulsing; }
		Blinking getBlinking() const { return blinking; }
		Normal getNormalSettings() const { return normal; }
		FadeInFadeOut getFadeInFadeOutSettings() const { return fadeInOut; }

	private:
#endif // __XAVIER
		bool    enabled;
		uint8_t current_value;
		Mode	mode;

		union __NO_PADDING__
		{
			Pulsing			pulsing;
			Blinking		blinking;
			Normal			normal;
			FadeInFadeOut	fadeInOut;
		};
	};

#if defined(__XAVIER)
	Led frontInfo() const { return front; }
	Led rearInfo() const  { return rear; }
private:
#endif // __XAVIER

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
			Open,
			Closed,
			Closing,
			Opening
		};
#if defined(__XAVIER)
		Leg() { memset(this, 0, sizeof(Leg)); }

		Status getStatus() const { return status; }
		uint8_t getValue() const { return value; }
		uint16_t getCurrent() const { return current; }

	private:
#endif
		Status	 status;
		uint8_t  value;
		uint16_t current;
	};

#if defined(__XAVIER)
	Leg frontInfo() const { return front; }
	Leg rearInfo() const { return rear; }
private:
#endif

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
		Lifting,
		Halted,
		Lowered,
		Home
	};

#if defined(__XAVIER)
	Status	 getStatus() const { return status; }
	float	 getPosition() const { return position; }
	uint16_t getCurrent() const { return current; }
private:
#endif
	uint16_t current;
	float  position;
	Status 	 status;

public:
	WinchInfo();
};
#endif 

struct BINDINGS_API __NO_PADDING__ Error
{
	enum class Code : uint8_t
	{
		Other = 0,
		LatchFailedToClose,
		LatchFailedToOpen,
		LatchBatteryEmpty,
		UnknownPacket
	};

#if defined(__XAVIER)
	Code getCode() const { return code; }
	const char* getMessage() const { return message; }
private:
#endif
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
#endif
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
#endif
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
		#define THIS_DEVICE		Device::Xavier
	#elif THIS_DEVICE == 2
		#define THIS_DEVICE		Device::Hook
	#elif THIS_DEVICE == 3
		#define THIS_DEVICE		Device::MainController
	#else
		#warning "THIS_DEVICE macro has invalid value."
		#define THIS_DEVICE Device::Unknown
	#endif
#else
	#warning "THIS_DEVICE macro is not defined."
	#define THIS_DEVICE Device::Unknown
#endif

#if defined(DEFAULT_RECEIVER_DEVICE)
	#if DEFAULT_RECEIVER_DEVICE == 1		
		#define DEFAULT_RECEIVER_DEVICE		Device::Xavier
	#elif DEFAULT_RECEIVER_DEVICE == 2
		#define DEFAULT_RECEIVER_DEVICE		Device::Hook
	#elif DEFAULT_RECEIVER_DEVICE == 3
		#define DEFAULT_RECEIVER_DEVICE		Device::MainController
	#else
		#warning "DEFAULT_RECEIVER_DEVICE macro has invalid value."
		#define DEFAULT_RECEIVER_DEVICE Device::Unknown
	#endif
#else
	#warning "DEFAULT_RECEIVER_DEVICE macro is not defined."
	#define DEFAULT_RECEIVER_DEVICE Device::Unknown
#endif

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
		LatencyCheck
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
		LandingGearInfo	landingGear;
		LedInfo	 		led;
		WinchInfo  		winch;
#endif
		Error		 	error;
		Warning		 	warning;
		LatencyCheck 	latencyCheck;
	};

	char endByte;

	Packet();
};

typedef HookInfo::Battery	Battery;
typedef HookInfo::Latch		Latch;
#if !defined(__HOOK)
typedef LedInfo::Led			Led;
typedef LandingGearInfo::Leg	Leg;
#endif

class PacketHandler
{
public:
	PacketHandler();

	void parseChar(char ch);

	bool packetAvailable();

	Packet getPacket();

	static Packet createError(Error err, Device device = DEFAULT_RECEIVER_DEVICE);

	static Packet createWarning(Warning warn, Device device = DEFAULT_RECEIVER_DEVICE);

	static Packet createMessage(const char* msg, Device device = DEFAULT_RECEIVER_DEVICE);

	static Packet createCommand(Command cmd, Device device = DEFAULT_RECEIVER_DEVICE);

private:
	char 	m_buffer[32];
	uint8_t m_bufferIndex;
	bool 	m_startByteDetected;

	std::list<Packet> m_packets;
};

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