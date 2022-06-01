#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <ctime>
#include <chrono>
#include <string>
#include <vector>

enum LogType
{
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
};

struct LogEntry
{
    LogType type;
    std::string message;
};

class Logger
{
private:
    static const std::string Red() { return "\033[0;31m"; };
    static const std::string Green() { return "\033[1;32m"; };
    static const std::string Yellow() { return "\033[1;33m"; };
    static const std::string Reset() { return "\033[0m"; };
    static std::string Timestamp();

public:
    static std::vector<LogEntry> messages;
    static void Log(const std::string &message);
    static void Err(const std::string &message);
};

#endif