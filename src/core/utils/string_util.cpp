#include "string_util.h"
#include "logger.h"

TextLines StringUtil::ConvertNewText(const std::string& text, bool wordWrap, unsigned int maxCharactersPerLine) {
    static Logger *logger = Logger::GetInstance();
    std::vector<std::string> lines = {};
    if (wordWrap && text.length() > maxCharactersPerLine) {
        unsigned int lineCount = text.length() / maxCharactersPerLine;
        lineCount += text.length() % maxCharactersPerLine > 0 ? 1 : 0;
        logger->Debug(std::string("line count = " + std::to_string(lineCount)));
        unsigned int endPos = 0;
        for (unsigned int i = 0; i < lineCount; i++) {
            endPos = i < lineCount - 1 ? maxCharactersPerLine : text.length() - (i * maxCharactersPerLine);
            logger->Debug(std::string("end pos = " + std::to_string(endPos)));
            std::string lineText = text.substr(i * maxCharactersPerLine, endPos);
            logger->Debug("line text = " + lineText);
            lines.emplace_back(lineText);
        }
    } else {
        lines.emplace_back(text);
    }
    return TextLines{ lines };
}
