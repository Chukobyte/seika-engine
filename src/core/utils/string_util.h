#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <string>
#include <vector>

struct TextLines {
    std::vector<std::string> lines = {};
};

class StringUtil {
  public:
    static TextLines ConvertNewText(const std::string& text, bool wordWrap, unsigned int maxCharactersPerLine);
};


#endif //STRING_UTIL_H
