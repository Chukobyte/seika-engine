#include "string_util.h"
#include "logger.h"

namespace StringUtil {
std::vector<std::string> Split(const std::string &text, char sep) {
    std::vector<std::string> tokens;
    std::size_t start = 0, end = 0;
    while ((end = text.find(sep, start)) != std::string::npos) {
        tokens.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(text.substr(start));
    return tokens;
}

TextLines ConvertIntoWordWrappedLines(const std::string& text, bool wordWrap, unsigned int maxCharactersPerLine) {
    static Logger *logger = Logger::GetInstance();
    std::vector<std::string> lines = {};
    if (wordWrap && text.length() > maxCharactersPerLine) {
        std::string currentLineText;
        for (const std::string& word : Split(text)) {
            if (currentLineText.size() + word.size() <= maxCharactersPerLine) {
                currentLineText += word + " ";
            } else {
                if (currentLineText.empty()) {
                    currentLineText = word + " ";
                }
                lines.emplace_back(currentLineText);
                currentLineText.clear();
                // If still to big then let it be...
                currentLineText += word + " ";
            }
        }
        if (!currentLineText.empty()) {
            lines.emplace_back(currentLineText);
            currentLineText.resize(currentLineText.size() - 1);
        }

    } else {
        lines.emplace_back(text);
    }
    return TextLines{ lines };
}
}
