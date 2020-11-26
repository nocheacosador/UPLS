#include "serialport.h"

#if defined(__linux__) || defined(__linux)
	#include <fcntl.h> // Contains file controls like O_RDWR
	#include <errno.h> // Error integer and strerror() function
	#include <unistd.h> // write(), read(), close()
#else
	#error "Unsupported OS."
#endif

#include <cstring>
#include <iostream>
#include <filesystem>
#include "console_formating.h"

namespace fs = std::filesystem;

SerialPort::SerialPort() : m_serialPort(0), m_portName(nullptr), m_isOpen(false),
	m_baudRate(BaudRate::Unknown), m_dataBits(DataBits::Unknown),
	m_stopBits(StopBits::Unknown), m_parity(Parity::Unknown),
	m_flowControl(FlowControl::Unknown),
	m_receiverThread(nullptr), m_buffer(1024)
{

}

SerialPort::SerialPort(const char* portName) : m_serialPort(0), m_portName(nullptr), m_isOpen(false),
	m_baudRate(BaudRate::Unknown), m_dataBits(DataBits::Eight),
	m_stopBits(StopBits::Unknown), m_parity(Parity::Unknown),
	m_flowControl(FlowControl::Unknown),
	m_receiverThread(nullptr), m_buffer(1024)
{
	std::string temp(portName);
	setPort(temp);
}

SerialPort::~SerialPort()
{
	close();

	if (m_portName)
		delete[] m_portName;
}

std::list<std::string> SerialPort::listAvailablePorts()
{	
	std::list<std::string> result;

#if defined(__linux__) || defined(__linux)

	std::string path("/dev/serial/by-path");

	if (fs::exists(path))
	{
    for (const auto& entry : fs::directory_iterator(path))
	    {
			if (fs::is_symlink(entry.path()))
			{
				auto symlink_path = fs::read_symlink(entry.path());

				auto temp = entry.path().parent_path();
				temp /= symlink_path;

				result.push_back(temp.lexically_normal().string());
			}
		}
	}
	else
		return result;
#endif

	result.sort();

	return result;
}

bool SerialPort::open()
{
	bool success = false;

	if (m_portName)
	{
		std::cout << '[' << Format("SerialPort").color(Color::Magenta).bold() << "] " 
			<< "Opening " << Format(m_portName).color(Color::Yellow) << "...\n";
		
		m_serialPort = ::open(m_portName, O_RDWR);

		if (m_serialPort < 0)
		{
			std::cerr << "[" << Format("Error").color(Color::Red).bold() << "] " << errno 
				<< ": from int open(const char*, int, ...) in SerialPort::open(): " << strerror(errno) << std::endl;
		}
		else
		{
			m_isOpen = true;
			
			termios tty;

			if (tcgetattr(m_serialPort, &tty) < 0)
			{
    			std::cerr << "[" << Format("Error").color(Color::Red).bold() << "] "<< errno << ": from int tcgetattr(int, struct termios*) in SerialPort::open(): " 
					<< strerror(errno) << std::endl;
				return false;
			}

			tty.c_cflag |= CREAD | CLOCAL;	// Turn on READ & ignore ctrl lines (CLOCAL = 1)
			tty.c_lflag &= ~ICANON;			// Disable canonical mode
			tty.c_lflag &= ~ECHO; 			// Disable echo
			tty.c_lflag &= ~ECHOE; 			// Disable erasure
			tty.c_lflag &= ~ECHONL; 		// Disable new-line echo
			tty.c_lflag &= ~ISIG;			// Disable interpretation of INTR, QUIT and SUSP
			tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
			tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes
			tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
			tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
			// tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT IN LINUX)
			// tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT IN LINUX)
			tty.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
			tty.c_cc[VMIN] = 0;

			if (tcsetattr(m_serialPort, TCSANOW, &tty) < 0) 
			{
				std::cerr << "[" << Format("Error").color(Color::Red).bold() << "] "<< errno << ": from int tcsetattr(int, int, const struct termios*) in SerialPort::open(): " 
					<< strerror(errno) << std::endl;
				return false;
			}

			setBaudRate(m_baudRate);
			setParity(m_parity);
			setFlowControl(m_flowControl);
			setDataBits(m_dataBits);
			setStopBits(m_stopBits);
			
			std::cout << '[' << Format("SerialPort").color(Color::Magenta).bold() << "] " 
			<< "Port successfully opened.\n";

			printSettings();

			std::cout << '[' << Format("SerialPort").color(Color::Magenta).bold() << "] Launching receiver thread...\n";
			m_receiverThread = new std::thread(&SerialPort::m_receiver, this);

			success = true;
		}
	}

	return success;
}

void SerialPort::close()
{
	if (m_isOpen)
	{
		m_isOpen = false;
		m_receiverThread->join();
		delete m_receiverThread;
		::close(m_serialPort);
		m_serialPort = 0;
	}
}

bool SerialPort::isOpened()
{
	return m_isOpen;
}

SerialPort& SerialPort::setPort(const std::string& portName)
{	
	if (portName.size() != 0)
	{
		if (m_portName)
			delete[] m_portName;

		m_portName = new char[portName.size()];
		memcpy(m_portName, portName.c_str(), portName.size());
	}
	else
	{
		std::cerr << "[" << Format("Error").color(Color::Red).bold() << "] From SerialPort::setPort(std::string& portName). portName.size() returned: "
			<< portName.size() << std::endl;
	}

	return *this;
}

std::string SerialPort::getPort()
{
	return std::string(m_portName);
}

SerialPort& SerialPort::setBaudRate(SerialPort::BaudRate baudRate)
{
	m_baudRate = baudRate;
	
	if (m_isOpen && baudRate != BaudRate::Unknown)
	{
		termios tty;
		
		if (tcgetattr(m_serialPort, &tty) < 0)
		{
    		std::cerr << "[" << Format("Error").color(Color::Red).bold() << "] "<< errno << ": from int tcgetattr(int, struct termios*) in SerialPort::setBaudRate(BaudRate): " 
				<< strerror(errno) << std::endl;
			return *this;
		}

		cfsetispeed(&tty, m_convertToSpeed_t(m_baudRate));
		cfsetospeed(&tty, m_convertToSpeed_t(m_baudRate));

		if (tcsetattr(m_serialPort, TCSANOW, &tty) < 0) 
			std::cerr << "[" << Format("Error").color(Color::Red).bold() << "] "<< errno << ": from int tcsetattr(int, int, const struct termios*) in SerialPort::setBaudRate(BaudRate): " 
				<< strerror(errno) << std::endl;
	}
	
	return *this;
}

SerialPort::BaudRate SerialPort::getBaudRate()
{
	if (m_isOpen)
	{
		termios tty;
		
		if (tcgetattr(m_serialPort, &tty) < 0)
		{
    		std::cerr << "[" << Format("Error").color(Color::Red).bold() << "] "<< errno << ": from int tcgetattr(int, struct termios*) in SerialPort::getBaudRate(): " 
				<< strerror(errno) << std::endl;
			m_baudRate = BaudRate::Unknown;
		}
		else
			m_baudRate = m_convertToBaudRate(cfgetispeed(&tty));
	}
	
	return m_baudRate;
}

SerialPort& SerialPort::setDataBits(SerialPort::DataBits dataBits)
{
	m_dataBits = dataBits;
	
	if (m_isOpen && dataBits != DataBits::Unknown)
	{
		termios tty;
		
		if (tcgetattr(m_serialPort, &tty) < 0)
		{
    		std::cerr<< "[" << Format("Error").color(Color::Red).bold() << "] "<< errno << ": from int tcgetattr(int, struct termios*) in SerialPort::setDataBits(DataBits): " 
				<< strerror(errno) << std::endl;
			return *this;
		}

		tty.c_cflag &= ~CSIZE;
		tty.c_cflag |= static_cast<uint32_t>(m_dataBits);

		if (tcsetattr(m_serialPort, TCSANOW, &tty) < 0) 
			std::cerr << "[" << Format("Error").color(Color::Red).bold() << "] "<< errno << ": from int tcsetattr(int, int, const struct termios*) in SerialPort::setDataBits(DataBits): " 
				<< strerror(errno) << std::endl;
	}

	return *this;
}

SerialPort::DataBits SerialPort::getDataBits()
{
	if (m_isOpen)
	{
		termios tty;
		
		if (tcgetattr(m_serialPort, &tty) < 0)
		{
    		std::cerr << "[" << Format("Error").color(Color::Red).bold() << "] "<< errno << ": from int tcgetattr(int, struct termios*) in SerialPort::getDataBits(): " 
				<< strerror(errno) << std::endl;
			m_dataBits = DataBits::Unknown;
		}
		else
			m_dataBits = static_cast<DataBits>(tty.c_cflag & CSIZE);
	}

	return m_dataBits;
}

SerialPort& SerialPort::setStopBits(SerialPort::StopBits stopBits)
{
	m_stopBits = stopBits;
	
	if (m_isOpen && stopBits != StopBits::Unknown)
	{
		termios tty;
		
		if (tcgetattr(m_serialPort, &tty) < 0)
		{
    		std::cerr << "[" << Format("Error").color(Color::Red).bold() << "] "<< errno << ": from int tcgetattr(int, struct termios*) in SerialPort::setStopBits(StopBits): " 
				<< strerror(errno) << std::endl;
			return *this;
		}

		tty.c_cflag &= ~CSTOPB;
		tty.c_cflag |= static_cast<uint32_t>(m_stopBits);

		if (tcsetattr(m_serialPort, TCSANOW, &tty) < 0) 
			std::cerr << "[" << Format("Error").color(Color::Red).bold() << "] "<< errno << ": from int tcsetattr(int, int, const struct termios*) in SerialPort::setStopBits(StopBits): " 
				<< strerror(errno) << std::endl;
	}

	return *this;
}

SerialPort::StopBits SerialPort::getStopBits()
{
	if (m_isOpen)
	{
		termios tty;
		
		if (tcgetattr(m_serialPort, &tty) < 0)
		{
    		std::cerr << "[" << Format("Error").color(Color::Red).bold() << "] "<< errno << ":from int tcgetattr(int, struct termios*) in SerialPort::getStopBits(): " 
				<< strerror(errno) << std::endl;
			m_stopBits = StopBits::Unknown;
		}
		else 
			m_stopBits = static_cast<StopBits>(tty.c_cflag & CSTOPB);
	}

	return m_stopBits;
}

SerialPort& SerialPort::setParity(SerialPort::Parity parity)
{
	m_parity = parity;
	
	if (m_isOpen && parity != Parity::Unknown)
	{
		termios tty;
		
		if (tcgetattr(m_serialPort, &tty) < 0)
		{
    		std::cerr << "[" << Format("Error").color(Color::Red).bold() << "] "<< errno << ": from int tcgetattr(int, struct termios*) in SerialPort::setParity(Parity): " 
				<< strerror(errno) << std::endl;
			return *this;
		}

		tty.c_cflag &= ~PARENB;
		tty.c_cflag |= static_cast<uint32_t>(m_parity);

		if (tcsetattr(m_serialPort, TCSANOW, &tty) < 0) 
			std::cerr << "[" << Format("Error").color(Color::Red).bold() << "] "<< errno << ": from int tcsetattr(int, int, const struct termios*) in SerialPort::setParity(Parity): " 
				<< strerror(errno) << std::endl;
	}
	
	return *this;
}

SerialPort::Parity SerialPort::getParity()
{
	if (m_isOpen)
	{
		termios tty;
		
		if (tcgetattr(m_serialPort, &tty) < 0)
		{
    		std::cerr << "[" << Format("Error").color(Color::Red).bold() << "] "<< errno << ": from int tcgetattr(int, struct termios*) in SerialPort::getParity(): " 
				<< strerror(errno) << std::endl;
			m_parity = Parity::Unknown;
		}
		else
			m_parity = static_cast<Parity>(tty.c_cflag & PARENB);
	}

	return m_parity;
}

SerialPort& SerialPort::setFlowControl(SerialPort::FlowControl flowControl)
{
	m_flowControl = flowControl;
	
	if (m_isOpen && flowControl != FlowControl::Unknown)
	{
		termios tty;
		
		if (tcgetattr(m_serialPort, &tty) < 0)
		{
    		std::cerr << "[" << Format("Error").color(Color::Red).bold() << "] "<< errno << ": from int tcgetattr(int, struct termios*) in SerialPort::setFlowControl(FlowControl): " 
				<< strerror(errno) << std::endl;
			return *this;
		}

		tty.c_cflag &= ~CRTSCTS;
		tty.c_cflag |= static_cast<uint32_t>(m_flowControl);

		if (tcsetattr(m_serialPort, TCSANOW, &tty) < 0) 
			std::cerr << "[" << Format("Error").color(Color::Red).bold() << "] "<< errno << ": from int tcsetattr(int, int, const struct termios*) in SerialPort::setFlowControl(FlowControl): " 
				<< strerror(errno) << std::endl;
	}
	
	return *this;
}

SerialPort::FlowControl SerialPort::getFlowControl()
{
	if (m_isOpen)
	{
		termios tty;
		
		if (tcgetattr(m_serialPort, &tty) < 0)
		{
    		std::cerr << "[" << Format("Error").color(Color::Red).bold() << "] "<< errno << ": from int tcgetattr(int, struct termios*) in SerialPort::getParity(): " 
				<< strerror(errno) << std::endl;
			m_flowControl = FlowControl::Unknown;
		}
		else
			m_flowControl = static_cast<FlowControl>(tty.c_cflag & CRTSCTS);
	}

	return m_flowControl;
}

void SerialPort::printSettings()
{
	std::cout << '[' << Format("SerialPort").color(Color::Magenta).bold() << "] " 
			<< Format("Port Name:    ").bold() << Format(m_portName).color(Color::Green) << std::endl;
	
	std::cout << '[' << Format("SerialPort").color(Color::Magenta).bold() << "] " 
			<< Format("Baud rate:    ").bold() << Format().color(Color::Yellow) << m_convertToInt(getBaudRate()) << Format().reset() << std::endl;

	std::cout << '[' << Format("SerialPort").color(Color::Magenta).bold() << "] " 
			<< Format("Data bits:    ").bold();
	switch (getDataBits())
	{
	case DataBits::Five:
		std::cout << Format("5\n").color(Color::Yellow);
		break;
	
	case DataBits::Six:
		std::cout << Format("6\n").color(Color::Yellow);
		break;

	case DataBits::Seven:
		std::cout << Format("7\n").color(Color::Yellow);
		break;
	
	case DataBits::Eight:
		std::cout << Format("8\n").color(Color::Yellow);
		break;

	default:
		std::cout << Format("unknown\n").color(Color::Red);
		break;
	}

	std::cout << '[' << Format("SerialPort").color(Color::Magenta).bold() << "] " 
			<< Format("Stop bits:    ").bold();
	switch (getStopBits())
	{
	case StopBits::Two:
		std::cout << Format("2\n").color(Color::Yellow);
		break;

	case StopBits::One:
		std::cout << Format("1\n").color(Color::Yellow);
		break;

	default:
		std::cout << Format("unknown\n").color(Color::Red);
		break;
	}

	std::cout << '[' << Format("SerialPort").color(Color::Magenta).bold() << "] " 
			<< Format("Parity:       ").bold();
	switch (getParity())
	{
	case Parity::Enabled:
		std::cout << Format("enabled\n").color(Color::Yellow);
		break;

	case Parity::Disabled:
		std::cout << Format("disabled\n").color(Color::Yellow);
		break;

	default:
		std::cout << Format("unknown\n").color(Color::Red);
		break;
	}

	std::cout << '[' << Format("SerialPort").color(Color::Magenta).bold() << "] " 
			<< Format("Flow Control: ").bold();
	switch (getFlowControl())
	{
	case FlowControl::Enabled:
		std::cout << Format("enabled\n").color(Color::Yellow);
		break;

	case FlowControl::Disabled:
		std::cout << Format("disabled\n").color(Color::Yellow);
		break;

	default:
		std::cout << Format("unknown\n").color(Color::Red);
		break;
	}

	std::cout << "\033[0m";
}

bool SerialPort::available()
{
	return !m_buffer.empty();
}

void SerialPort::putChar(const char ch)
{
	if (m_isOpen)
		::write(m_serialPort, &ch, 1);
}

void SerialPort::print(const char* str)
{
	if (m_isOpen)
	{
		size_t size = 0;

		while (str[size] != '\0')
		{
			if (size > 256)
			{
				std::cerr << "[" << Format("Error").color(Color::Red).bold() << "] in void SerialPort::print(const char* str): str is too big (max size is 256 bytes) or not null terminated.\n";
				return;
			}
			size++;
		}

		//std::lock_guard<std::mutex> lock(m_mux);
		int i = ::write(m_serialPort, str, size);
	}
}

void SerialPort::print(const std::string& str)
{
	if (m_isOpen)
	{
		//std::lock_guard<std::mutex> lock(m_mux);
		int i = ::write(m_serialPort, str.c_str(), str.size());
	}
}

void SerialPort::write(const void* data, size_t size)
{
	if (m_isOpen)
	{
		int i = ::write(m_serialPort, data, size);
	}
}

char SerialPort::getChar()
{
	return m_buffer.pop();
}

void SerialPort::m_receiver()
{
	char buffer[256];
	int bytes_read;

	while (m_isOpen)
	{
		bytes_read = read(m_serialPort, buffer, sizeof (buffer));
		
		if (bytes_read)
		{
			for (int i = 0; i < bytes_read; i++)
				m_buffer.push(buffer[i]);
		}
	}
}