#ifndef LOGGER_H
#define LOGGER_H

#include <cstdio>
#include <cstdarg> // For variadic functions support
#include <string>
#include <mutex>  // For std::mutex
#include <chrono> // For time-related functionalities

class Logger {
public:
    Logger(const std::string& outputFile, bool debugEnabled);
    ~Logger();

    void Log(const char* format, ...);
    void DebugLog(const char* format, ...);
    void EnableDebug(bool enable);

private:
    FILE* file;
    bool debug;
    mutable std::mutex logMutex; // Mutex for thread-safe logging

    std::string GetTimestamp() const; // Helper function to generate timestamps
    void LogHelper(const char* format, va_list args);
};

#endif // LOGGER_H
