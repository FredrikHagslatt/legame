#include "Logger.h"
#include "DevTools/LogWindow.h"
#include "DevTools/DevTools.h"

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
    std::string timestamp = Timestamp();
    LogEntry logEntry = {
        LOG_INFO,
        timestamp,
        message};

    if (DevTools::logToStdCout)
    {
        std::cout << Green() << "Log  [" << timestamp << "] : " << message << Reset();
    }
    SaveLogEntry(logEntry);
}

void Logger::Warning(const std::string &message)
{
    std::string timestamp = Timestamp();
    LogEntry logEntry = {
        LOG_WARNING,
        timestamp,
        message};
    if (DevTools::logToStdCout)
    {
        std::cout << Yellow() << "Warn [" << timestamp << "] : " << message << Reset();
    }
    SaveLogEntry(logEntry);
}

void Logger::Error(const std::string &message)
{
    std::string timestamp = Timestamp();
    LogEntry logEntry = {
        LOG_ERROR,
        timestamp,
        message};
    if (DevTools::logToStdCout)
    {
        std::cout << Red() << "Err  [" << timestamp << "] : " << message << Reset();
    }
    SaveLogEntry(logEntry);
}

void Logger::SaveLogEntry(LogEntry logEntry)
{
    messages.push_back(logEntry);
    if (DevTools::logToImGuiWindow)
    {
        DevTools::log.AddLog(logEntry.message.c_str());
        DevTools::log.AddLog("\n");
    }
}
