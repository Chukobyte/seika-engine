#include <catch.hpp>

#include <iostream>

#include "../../core/utils/string_util.h"
#include "../../core/ecs/component/components/text_label_component.h"

TEST_CASE("String Util Tests", "[string_util]") {

    SECTION("Convert New Text") {
        TextLabelComponent textLabelComponent = TextLabelComponent{
            "Testy texty to see how it works!",
            nullptr,
            Color(1.0f, 1.0f, 1.0f),
            true,
            5
        };
        TextLines textLines = StringUtil::ConvertNewText(textLabelComponent.text, textLabelComponent.wordWrap, textLabelComponent.maxCharactersPerLine);
        std::cerr << "text size = " << textLabelComponent.text.size() << std::endl;
        for (const std::string& text : textLines.lines) {
            std::cerr << text << std::endl;
        }
        REQUIRE(textLines.lines.size() == 7);
    }
}
