#ifndef COMMAND_LINE_FLAG_HELPER_H
#define COMMAND_LINE_FLAG_HELPER_H

#include "logger.h"

struct CommandLineFlagResult {
    std::string projectFilePath = "project.scfg";
    std::string workingDirectoryOverride;
    bool localAssets = false;
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
    const std::string FLAG_SET_PROJECT_STARTING_DIRECTORY0 = "-sd";
    const std::string FLAG_SET_PROJECT_STARTING_DIRECTORY1 = "-starting-directory";
    const std::string FLAG_SET_PROJECT_WORKING_DIRECTORY0 = "-d";
    const std::string FLAG_SET_PROJECT_WORKING_DIRECTORY1 = "-working-directory";
    const std::string FLAG_SET_LOCAL_ASSETS0 = "-la";
    const std::string FLAG_SET_LOCAL_ASSETS1 = "-local-assets";

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
            logger->Debug("project file path overridden to '" + commandLineFlagResult.projectFilePath + "'");
        } else if(argString == FLAG_SET_PROJECT_STARTING_DIRECTORY0 || argString == FLAG_SET_PROJECT_STARTING_DIRECTORY1) {
            FileHelper::ChangeDirectory(this->args[argumentIndex + 1]);
            logger->Debug("Project starting directory overridden to '" + std::string(this->args[argumentIndex + 1]) + "'");
        } else if(argString == FLAG_SET_PROJECT_WORKING_DIRECTORY0 || argString == FLAG_SET_PROJECT_WORKING_DIRECTORY1) {
            commandLineFlagResult.workingDirectoryOverride = this->args[argumentIndex + 1];
            logger->Debug("Working directory overridden to '" + commandLineFlagResult.workingDirectoryOverride + "'");
        } else if(argString == FLAG_SET_LOCAL_ASSETS0 || argString == FLAG_SET_LOCAL_ASSETS1) {
            std::string localAssetsFlag = std::string(this->args[argumentIndex + 1]);
            transform(localAssetsFlag.begin(), localAssetsFlag.end(), localAssetsFlag.begin(), ::tolower);
            if (localAssetsFlag != "false" && localAssetsFlag != "0") {
                commandLineFlagResult.localAssets = true;
                logger->Debug("Setting local assets flag to 'true'.");
            } else {
                commandLineFlagResult.localAssets = false;
                logger->Debug("Setting local assets flag to 'false'.");
            }
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
