#ifndef COMMAND_LINE_FLAG_HELPER_H
#define COMMAND_LINE_FLAG_HELPER_H

#include "logger.h"

struct CommandLineFlagResult {
    std::string projectFilePath = "project.json";
};

class CommandLineFlagHelper {
  private:
    int argv;
    char** args;
    CommandLineFlagResult commandLineFlagResult;
    Logger *logger = nullptr;

    const std::string FLAG_SET_LOG_LEVEL0 = "-l";
    const std::string FLAG_SET_LOG_LEVEL1 = "-log-level";
    const std::string FLAG_SET_PROJECT_FILE_PATH0 = "-p";
    const std::string FLAG_SET_PROJECT_FILE_PATH1 = "-project-file";

    CommandLineFlagResult ProcessArgument(int argumentIndex) {
        const std::string &argString = std::string(this->args[argumentIndex]);
        if (argString == FLAG_SET_LOG_LEVEL0 || argString == FLAG_SET_LOG_LEVEL1) {
            const std::string &logLevelString = std::string(this->args[argumentIndex + 1]);
            if (logger->SetLogLevelFromString(logLevelString)) {
                logger->Debug("Setting log level to '" + logLevelString + "'");
            } else {
                logger->Warn("'" + logLevelString + "' is an invalid log level!");
            }
        } else if(argString == FLAG_SET_PROJECT_FILE_PATH0 || argString == FLAG_SET_PROJECT_FILE_PATH1) {
            commandLineFlagResult.projectFilePath = std::string(this->args[argumentIndex + 1]);
        }
    }
  public:
    CommandLineFlagHelper() : logger(Logger::GetInstance()) {}

    CommandLineFlagResult ProcessCommandLineArgs(int argv, char** args) {
        this->argv = argv;
        this->args = args;

        if (this->argv > 1) {
            for (int argumentIndex = 0; argumentIndex < this->argv; argumentIndex++) {
                ProcessArgument(argumentIndex);
            }
        }
        return this->commandLineFlagResult;
    }
};

#endif //COMMAND_LINE_FLAG_HELPER_H
