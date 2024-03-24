#ifndef LOGGER_H
#define LOGGER_H

#include <cstdio>
#include <cstdarg>
#include <string>
#include <mutex>
#include <chrono>

#include <fmt/core.h>
#include <fmt/format.h>

class Logger {
public:
    // Singleton access method.
    static Logger& Get() {
        static Logger instance("default.log", false);
        return instance;
    }

    // Deleted to prevent copying and assignment.
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // Methods for logging.

    template<typename... Args>
    void Log(const std::string& format, Args... args);

    template<typename... Args>
    void DebugLog(const std::string& format, Args... args);

    // Enable or disable debug logging.
    void EnableDebug(bool enable);

    // Method to set or reset the configuration.
    static void SetConfig(const std::string& outputFile, bool debugEnabled);

    // Get the current timestamp as a string.
    std::string GetTimestamp() const;

    // Optionally public or private destructor. If public, ensures it can be called automatically at program termination.
    ~Logger() {
        if (file) {
            fclose(file);
        }
    }

private:
    // Private constructor to prevent external instantiation.
    Logger(const std::string& outputFile, bool debugEnabled);

    // Helper method for logging.
    void LogHelper(const std::string& message);

    FILE* file; // File pointer for the log file.
    bool debug; // Flag indicating whether debug logging is enabled.
    mutable std::mutex logMutex; // Mutex for thread-safe logging.
};

#include "Logger.inl"

#endif // LOGGER_H
