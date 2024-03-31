#include "Logger.h"
#include <filesystem>
#include <chrono>
#include <sstream>
#include <cstdarg>
#include <cstdio>  // For vsnprintf
#include <fmt/core.h> // For basic formatting
#include <fmt/format.h> // For more complex formatting, if needed

Logger::Logger(const std::string& outputFile, bool debugEnabled)
    : debug(debugEnabled) {
    std::filesystem::path logFilePath = std::filesystem::current_path() / outputFile;
    fopen_s(&file, logFilePath.string().c_str(), "a");
    if (file == nullptr) {
        // If opening the file fails, print to stderr
        fprintf(stderr, "Failed to open log file: %s\n", logFilePath.string().c_str());
    }
}

void Logger::SetConfig(const std::string& outputFile, bool debugEnabled) {
    Logger& instance = Logger::Get(); // Obtain the Singleton instance

    std::lock_guard<std::mutex> lock(instance.logMutex); // Use instance's mutex for thread-safety

    if (instance.file) {
        fclose(instance.file); // Close the current file if open
        instance.file = nullptr;
    }

    instance.debug = debugEnabled; // Update the debug flag

    // Attempt to open the new log file
    std::filesystem::path logFilePath = std::filesystem::current_path() / outputFile;
    fopen_s(&instance.file, logFilePath.string().c_str(), "a");
    if (instance.file == nullptr) {
        fprintf(stderr, "Failed to open log file: %s\n", logFilePath.string().c_str());
    }
}


void Logger::LogHelper(const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);

    if (!file) return;

    // Generate timestamp and prepend it to the log message
    std::string timestampedMessage = fmt::format("[{}] {}\n", GetTimestamp(), message);

    // Write the message to the log file and flush
    fputs(timestampedMessage.c_str(), file);
    fflush(file);

    // Also, print the message to the console
    fmt::print("{}", timestampedMessage);
}

void Logger::EnableDebug(bool enable) {
    std::lock_guard<std::mutex> lock(logMutex);
    debug = enable;
}

std::string Logger::GetTimestamp() const {
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::tm bt{};
#ifdef _WIN32
    localtime_s(&bt, &now_c);
#else
    localtime_r(&now_c, &bt);
#endif
    std::stringstream timeStream;
    timeStream << std::put_time(&bt, "%Y-%m-%d %H:%M:%S");
    return timeStream.str();
}
