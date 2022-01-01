#include <catch.hpp>

#include <iostream>

#include "../../core/global_dependencies.h"

#include "../../core/ecs/entity/system/text_rendering_entity_system.h"

class TestTextRenderingEntitySystem : public TextRenderingEntitySystem {
  public:
    TextLines ConvertNewText(const TextLabelComponent& textLabelComponent) override {
        return TextRenderingEntitySystem::ConvertNewText(textLabelComponent);
    }

//    TextLines ConvertNewText(const TextLabelComponent& textLabelComponent) {
//        Logger *logger = Logger::GetInstance();
//        std::vector<std::string> lines = {};
//        if (textLabelComponent.wordWrap && textLabelComponent.text.length() > textLabelComponent.maxCharactersPerLine) {
//            unsigned int lineCount = textLabelComponent.text.length() / textLabelComponent.maxCharactersPerLine;
//            lineCount += textLabelComponent.text.length() % textLabelComponent.maxCharactersPerLine > 0 ? 1 : 0;
//            logger->Debug(std::string("line count = " + std::to_string(lineCount)));
//            unsigned int endPos = 0;
//            for (unsigned int i = 0; i < lineCount; i++) {
////                endPos = i < lineCount - 1 ? endPos + textLabelComponent.maxCharactersPerLine : textLabelComponent.text.length();
//                endPos = i < lineCount - 1 ? textLabelComponent.maxCharactersPerLine : textLabelComponent.text.length() - (i * textLabelComponent.maxCharactersPerLine);
////                logger->Debug(std::string("end pos = " + std::to_string(endPos)));
//                std::cerr << "end pos = " << endPos << std::endl;
//                std::string lineText = textLabelComponent.text.substr(i * textLabelComponent.maxCharactersPerLine, endPos);
//                logger->Debug("line text = " + lineText);
//                lines.emplace_back(lineText);
//            }
//        } else {
//            lines.emplace_back(textLabelComponent.text);
//        }
//        return TextLines{ lines };
//    }
};

TEST_CASE("Text Rendering Entity System Tests", "[text_rendering_entity_system]") {

    SECTION("Convert New Text") {
        TestTextRenderingEntitySystem textRenderingEntitySystem;
        TextLabelComponent textLabelComponent = TextLabelComponent{
            "Test text to see how it works!",
            nullptr,
            Color(1.0f, 1.0f, 1.0f),
            true,
            5
        };
        TextLines textLines = textRenderingEntitySystem.ConvertNewText(textLabelComponent);
        std::cerr << "text size = " << textLabelComponent.text.size() << std::endl;
        for (const std::string& text : textLines.lines) {
            std::cerr << text << std::endl;
        }
        REQUIRE(textLines.lines.size() == 6);
    }
}
