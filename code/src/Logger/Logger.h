#pragma once
#include <stdint.h>
#include <string>
#include <array>


#define LOG_INFO(message,tag) Logger::LoggerSystem::Log(Logger::LogLevel::INFO, message, tag)
#define LOG_VERBOSE(message,tag)Logger::LoggerSystem::Log(Logger::LogLevel::VERBOSE, message, tag)
#define LOG_DEBUG(message,tag) Logger::LoggerSystem::Log(Logger::LogLevel::DEBUG, message, tag)
#define LOG_ERROR(message,tag) Logger::LoggerSystem::Log(Logger::LogLevel::ERROR, message, tag)
namespace Logger {
	enum class LogLevel: uint8_t {
		VERBOSE,
		DEBUG,
		INFO,
		ERROR,
		LAST
	};
	class ILogger {
	public:
		virtual void Log(LogLevel level, std::string message, std::string tag) = 0;
	private:
	};

	class StdIOLogger : public ILogger {
	public:
		virtual void Log(LogLevel level, std::string message, std::string tag) override;
	};

	class LoggerSystem {
	private:
		static std::unique_ptr<ILogger> m_logger;
	public:
		static void Log(LogLevel level, std::string message, std::string tag);
		static void InitLogger(std::unique_ptr<ILogger> m_logger);
	};
}