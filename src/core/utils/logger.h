#pragma once

#include "singleton.h"

#include <string>

typedef int LogLevel;
enum _LogLevel {
    LogLevel_DEBUG = 0,
    LogLevel_WARN = 1,
    LogLevel_INFO = 2,
    LogLevel_ERROR = 3,
};

class Logger : public Singleton<Logger> {
  private:
    void LogEntry(const std::string &logLevelPrefix, const std::string &logMessage) const;
  public:
    Logger(singleton) {}

    LogLevel logLevel = LogLevel_INFO;

    void SetLogLevel(LogLevel level);

    bool SetLogLevelFromString(std::string logLevelString);

    LogLevel GetLogLevel() const;
    void Debug(const std::string &logMessage) const;
    void Warn(const std::string &logMessage) const;
    void Info(const std::string &logMessage) const;
    void Error(const std::string &logMessage) const;

    void LogOpenGLError(const std::string &context) const;
};
