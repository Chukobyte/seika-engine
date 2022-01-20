#include "logger.h"

#include <iostream>
#include <bits/stdc++.h>
#include <glad/glad.h>

void Logger::SetLogLevel(LogLevel level) {
    logLevel = level;
}

bool Logger::SetLogLevelFromString(std::string logLevelString) {
    transform(logLevelString.begin(), logLevelString.end(), logLevelString.begin(), ::tolower);
    if (logLevelString == "debug") {
        logLevel = LogLevel_DEBUG;
        return true;
    } else if (logLevelString == "warn") {
        logLevel = LogLevel_WARN;
        return true;
    } else if (logLevelString == "info") {
        logLevel = LogLevel_INFO;
        return true;
    } else if (logLevelString == "error") {
        logLevel = LogLevel_ERROR;
        return true;
    }
    return false;
}

LogLevel Logger::GetLogLevel() const {
    return logLevel;
}

void Logger::Debug(const std::string &logMessage) const {
    if (logLevel <= LogLevel_DEBUG) {
        LogEntry("[DEBUG] ", logMessage);
    }
}

void Logger::Warn(const std::string &logMessage) const {
    if (logLevel <= LogLevel_WARN) {
        LogEntry("[WARN] ", logMessage);
    }
}

void Logger::Info(const std::string &logMessage) const {
    if (logLevel <= LogLevel_INFO) {
        LogEntry("[INFO] ", logMessage);
    }
}

void Logger::Error(const std::string &logMessage) const {
    if (logLevel <= LogLevel_ERROR) {
        LogEntry("[ERROR] ", logMessage);
    }
}

void Logger::LogEntry(const std::string &logLevelPrefix, const std::string &logMessage) const {
    std::cout << logLevelPrefix << logMessage << std::endl;
}

void Logger::LogOpenGLError(const std::string &context) const {
    GLuint err =glGetError();
    if (err > 0) {
        std::cout << "0x" << std::hex << err << " glGetError() in " << context << std::endl;
    }
}
