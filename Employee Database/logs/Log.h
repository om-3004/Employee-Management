#ifndef _LOG_H
#define _LOG_H

#include <iostream>
#include <chrono>
#include <string>
#include "string.h"
#include "FileDump.h"

namespace LogSystem {

	class Log
	{
	public:
		enum Level {
			LevelDebug,
			LevelInfo,
			LevelWarning,
			LevelError,
			LevelCritical
		};
		Log(const std::string& name) : m_NameLogger{ name }, m_Date{ getStrDateTime() } {}
		Log(const std::string& name, const Level& level) : m_NameLogger{ name }, m_LogLevel{ level }, m_Date{ getStrDateTime() } {}
		Log(const std::string& name, const Level& level, const std::string& file) : m_NameLogger{ name }, m_LogLevel{ level }, m_FileName{ file }, m_Date{ getStrDateTime() }, dumpInFile{ true } {}

		~Log() {
			if (dumpInFile && countLogs < 5) {
				fileDump f{ m_FileName };
				f.flushStream(m_BufferLog);
				m_BufferLog = "";
				countLogs = 0;
			}
		}

		void SetLogLevel(const Level& level) {
			m_LogLevel = level;
		}
		Level getLogLevel() const {
			return m_LogLevel;
		}

		template<typename ...Args>
		void log(const std::string& msg, const Level& level, Args ...args);

		template<typename ...Args>
		void Debug(const std::string& msg, Args ...args);
		template<typename ...Args>
		void Error(const std::string& msg, Args ...args);
		template<typename ...Args>
		void Warn(const std::string& msg, Args ...args);
		template<typename ...Args>
		void Info(const std::string& msg, Args ...args);
		template<typename ...Args>
		void Critical(const std::string& msg, Args ...args);

		void print() { std::cout << '\n'; }
		template<typename T, typename ...Args>
		void print(T arg, Args ...args) {
			std::cout << arg << " ";
			print(args...);
		}

		void appendBuffer() { m_BufferLog.append("\n\n"); }
		template<typename T, typename ...Args>
		void appendBuffer(T arg, Args ...args) {
			m_BufferLog.append(arg).append(" ");
			appendBuffer(args...);
		}

		bool dumpInFile{ false };

	private:
		short int countLogs{ 0 };

		Level m_LogLevel;
		std::string m_Date;

		std::string m_NameLogger;
		std::string m_BufferLog{ "" };
		std::string m_FileName{ "default-log.txt" };

		std::string stringLevel(const Level& level) {
			switch (level) {
			case LevelDebug:
				return "\033[0;35m[ DEBUG ]\033[0m";
			case LevelInfo:
				return "\033[0;36m[ INFO ]\033[0m";
			case LevelWarning:
				return "\033[1;33m[ WARNING ]\033[0m";
			case LevelError:
				return "\033[1;31m[ ERROR ]\033[0m";
			case LevelCritical:
				return "\033[0;31m[ CRITICAL ]\033[0m";
			}
			return "";
		}

		std::string stringLevelFile(const Level& level) {
			switch (level) {
			case LevelDebug:
				return "[ DEBUG ]";
			case LevelInfo:
				return "[ INFO ]";
			case LevelWarning:
				return "[ WARNING ]";
			case LevelError:
				return "[ ERROR ]";
			case LevelCritical:
				return "[ CRITICAL ]";
			}
			return "";
		}

		std::string getStrDateTime() {
			auto now = std::chrono::system_clock::now();
			auto currTime = std::chrono::system_clock::to_time_t(now);

			std::tm localTime;
			localtime_s(&localTime, &currTime);

			std::string res = std::to_string(localTime.tm_mday);

			res.append("/").append(std::to_string(localTime.tm_mon + 1)).append("/").append(std::to_string(localTime.tm_year + 1900))
				.append(" ").append(std::to_string(localTime.tm_hour)).append(":").append(std::to_string(localTime.tm_min))
				.append(":").append(std::to_string(localTime.tm_sec));
			return res;
		}

	};

	template<typename ...Args>
	void Log::Debug(const std::string& msg, Args ...args) {
		log(msg, LevelDebug, args...);
	}

	template<typename ...Args>
	void Log::Info(const std::string& msg, Args ...args) {
		log(msg, LevelInfo, args...);
	}

	template<typename ...Args>
	void Log::Warn(const std::string& msg, Args ...args) {
		log(msg, LevelWarning, args...);
	}

	template<typename ...Args>
	void Log::Error(const std::string& msg, Args ...args) {
		log(msg, LevelError, args...);
	}

	template<typename ...Args>
	void Log::Critical(const std::string& msg, Args ...args) {
		log(msg, LevelCritical, args...);
	}
}

#endif