#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <string>
#include <vector>

struct TextLines {
    std::vector<std::string> lines = {};
};

class StringUtil {
  public:
    static std::vector<std::string> Split(const std::string &text, char sep = ' ');
    static TextLines ConvertIntoWordWrappedLines(const std::string& text, bool wordWrap, unsigned int maxCharactersPerLine);
};


#endif //STRING_UTIL_H
