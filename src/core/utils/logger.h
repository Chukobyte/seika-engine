#ifndef LOGGER_H
#define LOGGER_H

#include <string>

typedef int LogLevel;
enum _LogLevel {
    LogLevel_DEBUG = 0,
    LogLevel_WARN = 1,
    LogLevel_INFO = 2,
    LogLevel_ERROR = 3,
};

class Logger {
  private:
    static Logger *instance;
    Logger() {}
    void LogEntry(const std::string &logLevelPrefix, const std::string &logMessage) const;
  public:

    LogLevel logLevel = LogLevel_DEBUG;

    static Logger* GetInstance() {
        if (!instance) {
            instance = new Logger();
        }
        return instance;
    }

    void SetLogLevel(LogLevel level);

    bool SetLogLevelFromString(std::string logLevelString);

    LogLevel GetLogLevel() const;
    void Debug(const std::string &logMessage) const;
    void Warn(const std::string &logMessage) const;
    void Info(const std::string &logMessage) const;
    void Error(const std::string &logMessage) const;
};

#endif //LOGGER_H
