#include "Logger.h"
#include <iostream>
#include <array>
namespace Logger {

std::array<std::string, static_cast<size_t>(LogLevel::LAST)> s_enumStringLookup = {
	"VERBOSE",
	"DEBUG",
	"INFO",
	"ERROR"
};
void StdIOLogger::Log(LogLevel level, std::string message, std::string tag)
{
	std::string msg = "[" + s_enumStringLookup[static_cast<size_t>(level)]+ "]" +
					"[" + tag + "]: "+ message;
	std::cout << msg << std::endl;
}

std::unique_ptr<ILogger> LoggerSystem::m_logger = nullptr;

void LoggerSystem::Log(LogLevel level, std::string message, std::string tag)
{
	if (m_logger == nullptr)
	{
		std::cout << "Logger wasn't initialized" << std::endl;
		return;
	}
	m_logger->Log(level, message, tag);
}
void LoggerSystem::InitLogger(std::unique_ptr<ILogger> i_logger)
{
	m_logger = std::move(i_logger);
}
}
