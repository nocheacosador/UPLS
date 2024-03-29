#ifndef UPLS_CONTROLLER_H
#define UPLS_CONTROLLER_H

#include <string>
#include <list>
#include <thread>
#include <shared_mutex>
#include <mutex>
#include <atomic>
#include "global_macros.h"
#include "serialport.h"
#include "tsqueue.h"
#include "packet.h"

/**
 * \brief Class for controlling various peripherals on the UAV.
 * Provides various functions to control UPLS 
 */
class BINDINGS_API UPLS_Controller
{
public:
	/**  
	 * \brief Default constructor for the UPLS_Controller object.
	 */
	UPLS_Controller();

	/**  
	 * \brief Deconstructor for the UPLS_Controller object.
	 */
	~UPLS_Controller();
	
	/**
	 * \brief Utility function for listing available serial ports.
	 * 
	 * Returns list of available serial port names. 
	 * If none found return empty list.
	 * 
	 * \return String list of ports names.
	 */
	std::list<std::string> listAvailablePorts();
	
	/**
	 * \brief Utility function to check for available serial ports.
	 * 
	 * Prints asout available serial ports if any.
	 */
	void printAvailablePorts();
	
	/**
	 * \brief Utility function for setting serial port which will be used.
	 * 
	 * Sets serial port which will be used for communication with UPLS.
	 * @param portName - Name of the port that will be used for connection.
	 */
	void setSerialPort(const char* portName);
	
	/**
	 * \brief Starts serial comunication with UPLS.
	 * \return Returns true on succesful connection.
	 */
	bool start();

	/**
	 * \brief Stops serial comunication with UPLS.
	 */
	void stop();
	
	/**
	 * \brief Utility function for checking if packet logging is enabled.
	 * \return Returns true if enabled, flase if disabled.
	 */
	bool receivedPacketLoggingEnabled();

	/**
	 * \brief Utility function enabling packet logging.
	 */
	void enableReceivedPacketLogging(bool enable);

	/**
	 * \brief Checks if any errors have been received or occured.
	 * \return Returns true if any errors have been received or occured.
	 */
	bool errorsOccured();
	
	Error getError();

	/**
	 * \brief Prints error that occured.
	 * Prints oldest error that occured and deletes it from the queue.
	 */
	void printError();
	
	/**
	 * \brief Prints all errors that occured.
	 * Prints all errors that occured without deleting them from the error queue.
	 */
	void printAllErrors();
	
	/**
	 * \brief Clears error queue.
	 * Deletes all errors from the queue.
	 */
	void clearAllErrors();
	
	/**
	 * \brief Checks if any warnings have been received or occured.
	 * \return Returns true if any warnings have been received or occured.
	 */
	bool warningsReceived();

	/**
	 * \brief Prints warning that occured.
	 * Prints oldest warning that occured and deletes it from the queue.
	 */
	void printWarning();

	/**
	 * \brief Prints all warnings that occured.
	 * Prints all warnings that occured without deleting them from the warning queue.
	 */
	void printAllWarnings();

	/**
	 * \brief Clears warning queue.
	 * Deletes all warnings from the queue.
	 */
	void clearAllWarnings();

	/**
	 * \brief Checks if any messages available.
	 * \return Returns true if any messages are available.
	 */
	bool messagesReceived();

	/**
	 * \brief Prints all messages in the queue.
	 * Prints and deletes all messages in the queue.
	 */
	void printAllMessages();

	/**
	 * \brief Access function.
	 * Returns object, containing latest information about UAV's hook.
	 * \return Returns latest hook information.
	 */
	HookInfo hookInfo();

	/**
	 * \brief Access function.
	 * Returns object, containing latest information about UAV's landing gear.
	 * \return Returns latest landing gear information.
	 */
	LandingGearInfo landingGearInfo();
	
	/**
	 * \brief Access function.
	 * Returns object, containing latest information about UAV's LEDs.
	 * \return Returns latest LEDs information.
	 */
	LedInfo ledInfo();
	
	/**
	 * \brief Access function.
	 * Returns object, containing latest information about UAV's winch.
	 * \return Returns latest winch information.
	 */
	WinchInfo winchInfo();

	/**
	 * \brief Access function.
	 * Returns object, containing latest information about UAV's UPLS controller.
	 * \return Returns latest UPLS's main controller information.
	 */
	MainControllerInfo mainControllerInfo();

	/**
	 * \brief Utility function.
	 * Returns current information about hook update frequency.
	 * \return Returns update frequeny in hertz.
	 */
	float hookInfoUpdateFrequency();

	/**
	 * \brief Utility function.
	 * Returns current information about landing gear update frequency.
	 * \return Returns update frequeny in hertz.
	 */
	float landingGearInfoUpdateFrequency();

	/**
	 * \brief Utility function.
	 * Returns current information about LEDs update frequency.
	 * \return Returns update frequeny in hertz.
	 */
	float ledInfoUpdateFrequency();

	/**
	 * \brief Utility function.
	 * Returns current information about winch update frequency.
	 * \return Returns update frequeny in hertz.
	 */
	float winchInfoUpdateFrequency();

	/**
	 * \brief Utility function.
	 * Returns current information about UAV's UPLS controller update frequency.
	 * \return Returns update frequeny in hertz.
	 */
	float mainControllerInfoUpdateFrequency();
	
	/**
	 * \brief Test function.
	 */
	void ledsOn();
	void ledsOff();
	void ledsEnable();
	void ledsDisable();
	void ledsSetMode(LedInfo::Led::Mode mode);
	void ledsSetSettings(LedInfo::Led::Settings settings);

	void latchOpen();

	void latchClose();

	void latchSetOpenPulseDuration(int pulse_duration);

	void latchSetClosePulseDuration(int pulse_duration);

	void hookShutdown();

	void landingGearExtract();

	void landingGearRetract();

	void winchManualUp(float speed = 0.5f, float duration = 0.1f);

	void winchManualDown(float speed = 0.5f, float duration = 0.1f);

	void winchLower(float distance);

	void winchHome();

	void winchHalt();

	void winchResume();

	void winchManualModeEnable();

	void winchManualModeDisable();

	/**
	 * \brief Formats and prints string as an error.
	 * Formats and prints string as an error in to stdout.
	 * \param error_msg Pointer to a C style string.
	 */
	void error(const char* error_msg);

	/**
	 * \brief Formats and prints string as an warning.
	 * Formats and prints string as an error in to stdout.
	 * \param warning_msg Pointer to a C style string.
	 */
	void warning(const char* warning_msg);

	/**
	 * \brief Formats and prints string as an message.
	 * Formats and prints string as an error in to stdout.
	 * \param message Pointer to a C style string.
	 */
	void message(const char* message);

private:
	SerialPort 	m_serial;

	std::atomic<bool> m_logReceivedPackets;
	std::atomic<bool> m_receiverRunning;
	std::thread* 	  m_receiverThread;

	tsqueue<Packet> m_errorQueue;
	tsqueue<Packet> m_warningQueue;
	tsqueue<Packet> m_messageQueue;

	HookInfo 		   m_hookInfo;
	LandingGearInfo    m_landingGearInfo;
	LedInfo			   m_ledInfo;
	WinchInfo		   m_winchInfo;
	MainControllerInfo m_mainControllerInfo;

	std::chrono::time_point<std::chrono::steady_clock> m_lastHookInfoUpdateTimePoint;
	std::chrono::time_point<std::chrono::steady_clock> m_lastLandingGearInfoUpdateTimePoint;
	std::chrono::time_point<std::chrono::steady_clock> m_lastLedInfoUpdateTimePoint;
	std::chrono::time_point<std::chrono::steady_clock> m_lastWinchInfoUpdateTimePoint;
	std::chrono::time_point<std::chrono::steady_clock> m_lastMainControllerInfoUpdateTimePoint;
	
	std::atomic<float> m_hookInfoUpdateFrequency;
	std::atomic<float> m_landingGearInfoUpdateFrequency;
	std::atomic<float> m_ledInfoUpdateFrequency;
	std::atomic<float> m_winchInfoUpdateFrequency;
	std::atomic<float> m_mainControllerInfoUpdateFrequency;


#if !defined(DOXYGEN_ONLY) && !defined(__BINDINGS)
protected:
	std::shared_mutex muxHookInfo;
	std::shared_mutex muxLandingGearInfo;
	std::shared_mutex muxLedInfo;
	std::shared_mutex muxWinchInfo;
	std::shared_mutex muxMainControllerInfo;
	std::mutex muxInfoStream;
#endif // !DOXYGEN_ONLY and !__BINDINGS

private:
	void m_receivedPacketHandler();
	void m_updateHookInfo(HookInfo& info);
	void m_updateLandingGearInfo(LandingGearInfo& info);
	void m_updateLedInfo(LedInfo& info);
	void m_updateWinchInfo(WinchInfo& info);
	void m_updateMainControllerInfo(MainControllerInfo& info);

	void info(const char* info_msg);
};

#endif // UPLS_CONTROLLER_H