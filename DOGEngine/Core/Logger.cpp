#include "Logger.h"
#include <filesystem> // C++17 filesystem
#include <array>
#include <chrono>
#include <sstream>
#include <cstdarg> // Needed for va_list and related operations



Logger::Logger(const std::string& outputFile, bool debugEnabled)
    : debug(debugEnabled) {
    // Get the current path and append the output file name to it
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path logFilePath = currentPath / outputFile;

    // Use fopen_s with the full path
    errno_t err = fopen_s(&file, logFilePath.string().c_str(), "a");
    if (err != 0) {
        // fopen_s returns a non-zero value if it fails to open the file
        fprintf(stderr, "Failed to open log file: %s\n", logFilePath.string().c_str());
        file = nullptr; // Ensure file pointer is null if open failed
    }
}

Logger::~Logger() {
    if (file) {
        fclose(file);
    }
}


void Logger::DebugLog(const char* format, ...) {
    if (!debug) return; // Check debug flag before proceeding

    // Prepare the full debug message format by prefixing [DEBUG] tag
    std::string debugFormat = "[DEBUG] " + std::string(format);

    // Since Log is a variadic function, we need to handle the forwarding of arguments
    va_list args;
    va_start(args, format);
    // Utilize Log function for actual logging
    LogHelper(debugFormat.c_str(), args);
    va_end(args);
}

void Logger::LogHelper(const char* format, va_list args) {
    std::lock_guard<std::mutex> lock(logMutex); // Ensure thread safety

    if (!file) return; // Return early if file isn't open

    // Generate the timestamp
    std::string timestamp = GetTimestamp();

    // Prepare a formatted string for the console
    std::string consoleMsg = "[" + timestamp + "] " + format + "\n";

    // Copy va_list for use with both file and console logging
    va_list args_copy;
    va_copy(args_copy, args);

    // Write to the log file
    fprintf(file, "[%s] ", timestamp.c_str());
    vfprintf(file, format, args);
    fprintf(file, "\n");
    fflush(file);

    // Also write the same message to the console
    vprintf(consoleMsg.c_str(), args_copy);

    // Clean up the va_list copy
    va_end(args_copy);
}

void Logger::Log(const char* format, ...) {
    va_list args;
    va_start(args, format);
    LogHelper(format, args);
    va_end(args);
}

void Logger::EnableDebug(bool enable) {
    std::lock_guard<std::mutex> lock(logMutex); // Ensure thread safety when toggling debug mode
    debug = enable;
}

std::string Logger::GetTimestamp() const {
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now); // Convert to time_t

    std::tm bt{};
#ifdef _WIN32
    localtime_s(&bt, &now_c); // Use localtime_s on Windows
#else
    // POSIX systems don't have localtime_s, use localtime_r if available
    localtime_r(&now_c, &bt);
#endif

    std::stringstream timeStream;
    timeStream << std::put_time(&bt, "%Y-%m-%d %H:%M:%S");
    return timeStream.str();
}
