#include "Logger.h" 
#include <iomanip> 
#include <ctime> 

Logger::Logger(std::string filename, LogLevel level) {
    m_logLevel = level;
    m_fileStream.open(filename.c_str(), std::ios::out | std::ios::app);
}

Logger::~Logger() {
    m_fileStream.close();
}

void Logger::setLogLevel(LogLevel level) {
    m_logLevel = level;
}

void Logger::log(std::string message, LogLevel level) { 
    if (level >= m_logLevel) {
        std::time_t t = std::time(nullptr);
        std::tm tm = *std::localtime(&t);

        std::string logLevelString = getLogLevelString(level); 
        std::time_t now = std::time(nullptr);
        std::tm tm_ = *std::localtime(&now);
        char buffer[100]; 
        std::strftime(buffer, 100, "%d.%m.%Y %H:%M:%S", &tm);
        std::string timestamp(buffer);
        std::string logMessage = "[" + timestamp + "] " + "[" + logLevelString + "] " + message;

        std::cout << logMessage << std::endl;
        m_fileStream << logMessage << std::endl;
    }
}

std::string Logger::getLogLevelString(LogLevel level) {
    switch (level) {
    case LogLevel::Info:
        return "INFO";
    case LogLevel::Debug:
        return "DEBUG";
    case LogLevel::Error:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}