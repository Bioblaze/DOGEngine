#include "Logger.h"
#include <filesystem> // C++17 filesystem
#include <array>

Logger::Logger(const std::string& outputFile, bool debugEnabled)
    : debug(debugEnabled) {
    // With C++17, we can use filesystem::path for more robust file path handling
    std::filesystem::path logFilePath(outputFile);
    file = fopen(logFilePath.string().c_str(), "a");
    if (!file) {
        fprintf(stderr, "Failed to open log file: %s\n", logFilePath.string().c_str());
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

    // Write the timestamp before the log message
    std::string timestamp = GetTimestamp();
    fprintf(file, "[%s] ", timestamp.c_str());

    // Write the formatted log message using vfprintf to handle va_list
    vfprintf(file, format, args);

    fprintf(file, "\n");
    fflush(file);
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
    using namespace std::chrono;

    // C++17 chrono improvements for more intuitive time handling
    auto now = system_clock::now();
    auto nowTimeT = system_clock::to_time_t(now);
    auto nowMs = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    std::tm bt;
#ifdef _WIN32
    localtime_s(&bt, &nowTimeT);
#else
    localtime_r(&nowTimeT, &bt); // POSIX
#endif

    // Use std::array to avoid magic numbers for buffer size
    std::array<char, 30> buffer;
    snprintf(buffer.data(), buffer.size(), "%04d-%02d-%02d %02d:%02d:%02d.%03d",
        bt.tm_year + 1900, bt.tm_mon + 1, bt.tm_mday,
        bt.tm_hour, bt.tm_min, bt.tm_sec, static_cast<int>(nowMs.count()));
    return std::string(buffer.data());
}
