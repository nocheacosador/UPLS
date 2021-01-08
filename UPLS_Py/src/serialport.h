#ifndef SERIALPORT_H_
#define SERIALPORT_H_

#include <list>
#include <array>
#include <string>
#include <mutex>
#include <thread>
#include <atomic>

#if defined(__linux__) || defined(__linux)
#include <termios.h> // Contains POSIX terminal control definitions
#endif

#include "ringbuffer.h"

#include <csignal>
#include <signal.h>

class SerialPort
{
public:
	enum class BaudRate
	{
		Baud1200 = B1200,
		Baud2400 = B2400,
		Baud4800 = B4800,
		Baud9600 = B9600,
		Baud19200 = B19200,
		Baud38400 = B38400,
		Baud57600 = B57600,
		Baud115200 = B115200,
		Unknown = -1
	};

	enum class DataBits
	{
		Five	= CS5,
		Six		= CS6,
		Seven	= CS7,
		Eight	= CS8,
		//Nine	= 9,
		Unknown = -1
	};
	
	enum class StopBits
	{
		One	= 0,
		Two = CSTOPB,
		Unknown = -1
	};

	enum class FlowControl
	{
		Enabled = int32_t(CRTSCTS),
		Disabled = 0,
		Unknown = -1
	};

	enum  class Parity
	{
		Enabled = PARENB,
		Disabled = 0,
		Unknown = -1
	};

	SerialPort();
	SerialPort(const char* portName);
	~SerialPort();

	static std::list<std::string> listAvailablePorts();

	bool open();

	void close();

	bool isOpened();

	SerialPort& setPort(const std::string& portName);
	std::string getPort();

	SerialPort& setBaudRate(BaudRate baudRate);
	BaudRate getBaudRate();

	SerialPort& setDataBits(DataBits dataBits);
	DataBits getDataBits();

	SerialPort& setStopBits(StopBits stopBits);
	StopBits getStopBits();

	SerialPort& setParity(Parity parity);
	Parity getParity();

	SerialPort& setFlowControl(FlowControl flowControl);
	FlowControl getFlowControl();

	void printSettings();

	bool available();

	void putChar(const char ch);

	void print(const char* str);

	void print(const std::string& str);

	void write(const void* data, size_t size);

	char getChar();

protected:
	std::mutex mux;

private:
	int m_serialPort;
	char* m_portName;
	std::atomic<bool> m_isOpen;

	std::thread* m_receiverThread;
	
	BaudRate m_baudRate;
	DataBits m_dataBits;
	StopBits m_stopBits;
	Parity   m_parity;
	FlowControl m_flowControl;

	RingBuffer<char, 1024> m_buffer;

	struct BaudRateConversionTableItem
	{
		BaudRate enumRate;
		speed_t  termosEnumRate;
		int 	 rawRate;

		BaudRateConversionTableItem(BaudRate er, speed_t ter, int raw) : enumRate(er), termosEnumRate(ter), rawRate(raw) { ; }
	};

	static const std::array<BaudRateConversionTableItem, 9> m_baudRateConversionTable;

	int m_convertToInt(BaudRate baudRate)
	{
		for (auto i : m_baudRateConversionTable)
			if (i.enumRate == baudRate)
				return i.rawRate;
		return -1;
	}

	int m_convertToInt(speed_t baudRate)
	{
		for (auto i : m_baudRateConversionTable)
			if (i.termosEnumRate == baudRate)
				return i.rawRate;
		return -1;
	}

	BaudRate m_convertToBaudRate(int baudRate)
	{
		for (auto i : m_baudRateConversionTable)
			if (i.rawRate == baudRate)
				return i.enumRate;
		return BaudRate::Unknown;
	}

	BaudRate m_convertToBaudRate(speed_t baudRate)
	{
		for (auto i : m_baudRateConversionTable)
			if (i.termosEnumRate == baudRate)
				return i.enumRate;
		return BaudRate::Unknown;
	}

	speed_t m_convertToSpeed_t(BaudRate baudRate)
	{
		for (auto i : m_baudRateConversionTable)
			if (i.enumRate == baudRate)
				return i.termosEnumRate;
		return -1;
	}

	speed_t m_convertToSpeed_t(int baudRate)
	{
		for (auto i : m_baudRateConversionTable)
			if (i.rawRate == baudRate)
				return i.termosEnumRate;
		return -1;
	}

	void m_receiver();
};

#endif // SERIALPORT_H_