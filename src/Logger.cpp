#include "Logger.h"

std::vector<LogEntry> Logger::messages;

std::string Logger::Timestamp()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string timestamp(30, '\0');
    std::strftime(&timestamp[0], timestamp.size(), "%y-%m-%d %H:%M:%S", std::localtime(&now));
    return timestamp;
}

void Logger::Log(const std::string &message)
{
    LogEntry logEntry = {
        LOG_INFO, 
        Green() + "Log [" + Timestamp() + "] : " + message + Reset()};
    std::cout << logEntry.message << std::endl;
    messages.push_back(logEntry);
}

void Logger::Err(const std::string &message)
{
    LogEntry logEntry = {
        LOG_ERROR,
        Red() + "Err [" + Timestamp() + "] : " + message + Reset()};
    std::cout << logEntry.message << std::endl;
    messages.push_back(logEntry);
}