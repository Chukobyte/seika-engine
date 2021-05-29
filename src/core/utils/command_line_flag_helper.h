#ifndef COMMAND_LINE_FLAG_HELPER_H
#define COMMAND_LINE_FLAG_HELPER_H

#include "logger.h"

class CommandLineFlagHelper {
  private:
    int argv;
    char** args;
    Logger *logger = nullptr;

    const std::string FLAG_SET_LOG_LEVEL0 = "-l";
    const std::string FLAG_SET_LOG_LEVEL1 = "-log-level";

    void ProcessArgument(int argumentIndex) {
        const std::string &argString = std::string(this->args[argumentIndex]);
        if (argString == FLAG_SET_LOG_LEVEL0 || argString == FLAG_SET_LOG_LEVEL1) {
            const std::string &logLevelString = std::string(this->args[argumentIndex + 1]);
            if (logger->SetLogLevelFromString(logLevelString)) {
                logger->Debug("Setting log level to '" + logLevelString + "'");
            } else {
                logger->Warn("'" + logLevelString + "' is an invalid log level!");
            }
        }
    }
  public:
    CommandLineFlagHelper() : logger(Logger::GetInstance()) {}

    void ProcessCommandLineArgs(int argv, char** args) {
        this->argv = argv;
        this->args = args;

        if (this->argv > 1) {
            for (int argumentIndex = 0; argumentIndex < this->argv; argumentIndex++) {
                ProcessArgument(argumentIndex);
            }
        }
    }
};

#endif //COMMAND_LINE_FLAG_HELPER_H
