#include <catch.hpp>

#include <iostream>

#include "../../core/global_dependencies.h"

#include "../../core/ecs/entity/system/text_rendering_entity_system.h"

class TestTextRenderingEntitySystem : public TextRenderingEntitySystem {
  public:
    TextLines ConvertNewText(const TextLabelComponent& textLabelComponent) override {
        return TextRenderingEntitySystem::ConvertNewText(textLabelComponent);
//        return TextLines{};
    }
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
        REQUIRE(textLines.lines.size() == 6);
    }
}
