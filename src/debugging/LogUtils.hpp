#pragma once
#include <format>
#include <iostream>

enum LogPriority {
    LOG_UNKNOWN = 0,
    LOG_DEFAULT,
    LOG_VERBOSE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL,
    LOG_SILENT,
};

#if DEBUG
const char* k_logPrefixes[] = {
    "[UNKNOWN]",
    "[DEFAULT]",
    "[VERBOSE]",
    "[DEBUG]",
    "[INFO]",
    "[WARN]",
    "[ERROR]",
    "[FATAL]",
    "[SILENT]"
};
#endif

template <typename... Args>
void _PrintWLog(LogPriority i_log, std::wformat_string<Args...> fmt, Args&&... args)
{
#if DEBUG
    std::wcout << k_logPrefixes[i_log] << " "
        << std::format(fmt, std::forward<Args>(args)...) << "\n";
#endif
}

template <typename... Args>
void _PrintLog(LogPriority i_log, std::format_string<Args...> fmt, Args&&... args)
{
#if DEBUG
    std::cout << k_logPrefixes[i_log] << " "
        << std::format(fmt, std::forward<Args>(args)...) << "\n";
#endif
}

#if DEBUG
#define WLOG(priority, fmt, ...) _PrintWLog(priority, fmt, ##__VA_ARGS__)
#define LOG(priority, fmt, ...) _PrintLog(priority, fmt, ##__VA_ARGS__)
#else
#define WLOG(priority, fmt, ...) ((void)0)
#define LOG(priority, fmt, ...) ((void)0)
#endif