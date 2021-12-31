#ifndef TEXT_LABEL_COMPONENT_H
#define TEXT_LABEL_COMPONENT_H

#include "../../../rendering/font.h"

#include "../../../color.h"

struct TextLabelComponent {
    std::string text;
    Font *font = nullptr;
    Color color;
//    bool wordWrap = false;
    bool wordWrap = true;
//    unsigned int maxCharacterOnLine = 999999999;
    unsigned int maxCharacterOnLine = 2;
    int newLinePadding = 2;
};

#endif //TEXT_LABEL_COMPONENT_H
