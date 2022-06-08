#include "Logger.h"

std::vector<LogEntry> Logger::messages;

std::string Logger::Timestamp()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string timestamp(30, '\0');
    std::strftime(&timestamp[0], timestamp.size(), "%y-%m-%d %H:%M:%S", std::localtime(&now));
    return timestamp;
}

void Logger::Info(const std::string &message)
{
    LogEntry logEntry = {
        LOG_INFO, 
        Green() + "Log [" + Timestamp() + "] : " + message + Reset()};
    std::cout << logEntry.message << std::endl;
    messages.push_back(logEntry);
}

void Logger::Error(const std::string &message)
{
    LogEntry logEntry = {
        LOG_ERROR,
        Red() + "Error [" + Timestamp() + "] : " + message + Reset()};
    std::cout << logEntry.message << std::endl;
    messages.push_back(logEntry);
}

void Logger::Fatal(const std::string &message)
{
    LogEntry logEntry = {
        LOG_FATAL,
        Red() + "FATAL [" + Timestamp() + "] : " + message + Reset()};
    std::cout << logEntry.message << std::endl;
    messages.push_back(logEntry);
    exit(EXIT_FAILURE);
}
