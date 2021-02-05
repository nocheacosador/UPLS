#pragma once

#include <fstream>
#include <ostream>
#include <sstream>
#include <list>
#include <functional>
#include <chrono>
#include "console_formating.h"
#include <mutex>
#include <filesystem>

namespace na
{
	template<typename _CharT>
	class BasicLogger
	{
	public:
		static BasicLogger& instance()
		{
			static BasicLogger* instance_ptr = nullptr;
		
			if (!instance_ptr)
			{
				instance_ptr = new BasicLogger();
			}
		
			return *instance_ptr;
		}

		template <typename... Types>
		void error(const Types&... args)
		{
			using namespace na::Console;
			using std::chrono::system_clock;
			
			auto systemClockNow = system_clock::now();
#ifndef LOG_NO_THREADSAFE
			std::scoped_lock lock(mux);
#endif

			m_header(m_formatTime(systemClockNow), Format("   ERROR").color(Color::BrightRed));
			m_print(args...);
		}

		template <typename... Types>
		void warning(const Types&... args)
		{
			using namespace na::Console;
			using std::chrono::system_clock;
			
			auto systemClockNow = system_clock::now();
#ifndef LOG_NO_THREADSAFE
			std::scoped_lock lock(mux);
#endif
			m_header(m_formatTime(systemClockNow), Format(" WARNING").color(Color::BrightYellow));
			m_print(args...);
		}

		template <typename... Types>
		void info(const Types&... args)
		{
			using namespace na::Console;
			using std::chrono::system_clock;
			
			auto systemClockNow = system_clock::now();
#ifndef LOG_NO_THREADSAFE
			std::scoped_lock lock(mux);
#endif
			m_header(m_formatTime(systemClockNow), Format("    INFO").color(Color::BrightCyan));
			m_print(args...);
		}

		template <typename... Types>
		void debug(const Types&... args)
		{
			using namespace na::Console;
			using std::chrono::system_clock;
			
			auto systemClockNow = system_clock::now();
#ifndef LOG_NO_THREADSAFE
			std::scoped_lock lock(mux);
#endif
			m_header(m_formatTime(systemClockNow), Format("   DEBUG").color(Color::BrightMagenta));
			m_print(args...);
		}

		BasicLogger& addStream(std::basic_ostream<_CharT>* os)
		{		
			using std::chrono::system_clock;
				
			auto rawTime = system_clock::to_time_t(system_clock::now());
			auto time = localtime(&rawTime);
			
			m_outputStreams.push_back(os);
			*os << "==============================[ LOG " << time->tm_hour << ':' << time->tm_min << ":" << time->tm_sec 
						<< " ]==============================\n";
			return *this;
		}

		BasicLogger& logToFile()
		{
			if (!m_logFile.is_open())
			{
				using std::chrono::system_clock;
				
				auto rawTime = system_clock::to_time_t(system_clock::now());
				auto time = localtime(&rawTime);
				char file_name[20]; 
				sprintf(file_name, "%d-%d-%d.log", time->tm_mday, time->tm_mon, time->tm_year + 1900);
				
				if (!std::filesystem::exists(m_logDir) || !std::filesystem::is_directory(m_logDir))
					std::filesystem::create_directory(m_logDir);

				std::filesystem::path logFilePath(m_logDir);
				logFilePath.append(file_name);
				m_logFile.open(logFilePath, std::ios::app);

				if (m_logFile.is_open())
				{
					addStream(&m_logFile);
				}
			}

			return *this;
		}

	private:
		BasicLogger() : m_logDir(std::filesystem::current_path()) 
		{
			m_logDir.append("log");
		}

		BasicLogger(const BasicLogger&) = delete;
		BasicLogger& operator = (const BasicLogger&) = delete;

		~BasicLogger()
		{
			if (m_logFile.is_open()) 
			{
				m_logFile.close();
			}
		}

		void m_print()
		{
			for (auto os : m_outputStreams)
				*os << std::endl;
		}

		template <typename T, typename... Types>
		void m_print(const T& arg, const Types&... args)
		{
			for (auto os : m_outputStreams)
				*os << arg;
			
			m_print(args...);
		}
		
		void m_headerInternal()
		{
			for (auto os : m_outputStreams)
				*os << "] ";
		}

		template <typename T, typename... Types>
		void m_headerInternal(const T& arg, const Types&... args)
		{
			for (auto os : m_outputStreams)
				*os << arg;

			m_headerInternal(args...);
		}

		template <typename... Types>
		void m_header(const Types&... args)
		{
			for (auto os : m_outputStreams)
				*os << '[';
			
			m_headerInternal(args...);
		}

		static std::basic_string<_CharT> m_formatTime(std::chrono::system_clock::time_point& timePoint)
		{
			using std::chrono::system_clock;
			using std::chrono::microseconds;
			using std::chrono::duration_cast;

			auto microsec = duration_cast<microseconds>(timePoint.time_since_epoch()).count();
			auto rawTime = system_clock::to_time_t(timePoint);
			auto time = localtime(&rawTime);

			char buf[40]; 
			sprintf(buf, "%d-%d-%d %02d:%02d:%02d.%06ld", time->tm_mday, time->tm_mon, time->tm_year + 1900,
												time->tm_hour, time->tm_min, time->tm_sec, microsec % 1000000);
			
			return std::basic_string<_CharT>(buf);
		}
	protected:
		mutable std::mutex mux;

	private:
		std::list<std::basic_ostream<_CharT>*> m_outputStreams;
		std::filesystem::path m_logDir;
		std::ofstream m_logFile;
	};

	typedef BasicLogger<char> Logger;

	extern Logger& log;
};