

template<typename... Args>
void Logger::Log(const std::string& format, Args... args) {

    // Use fmt::format to insert arguments into the format string.
    std::string formattedMessage = fmt::format(format, args...);

    LogHelper(formattedMessage);
}

template<typename... Args>
void Logger::DebugLog(const std::string& format, Args... args) {
    if (!debug) return;

    // Use fmt::format to insert arguments into the format string.
    std::string formattedMessage = fmt::format(format, args...);

    // Prefix [DEBUG] to the formatted message.
    formattedMessage = fmt::format("[DEBUG] {}", formattedMessage);

    // Now call LogHelper with the fully formatted message.
    LogHelper(formattedMessage);
}