#ifndef LOGGER_H 
#define LOGGER_H 

#include <iostream> 
#include <fstream> 
#include <string>

enum class LogLevel {
    Info,       
    Debug,       
    Error       
};

class Logger {
public: 
    Logger(std::string filename, LogLevel level = LogLevel::Info);

    ~Logger();

    void setLogLevel(LogLevel level);

    void log(std::string message, LogLevel level = LogLevel::Info);

private:
    LogLevel m_logLevel;            
    std::ofstream m_fileStream;     
 
    std::string getLogLevelString(LogLevel level);
};

#endif