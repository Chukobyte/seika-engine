#ifndef TEXT_RENDERING_ENTITY_SYSTEM_H
#define TEXT_RENDERING_ENTITY_SYSTEM_H

#include "../entity_system.h"
#include "../../component/components/transform2D_component.h"
#include "../../component/components/text_label_component.h"
#include "../../../math/space_handler.h"
#include "../../../utils/string_util.h"

class TextRenderingEntitySystem : public EntitySystem {
  private:
    Renderer2D *renderer = nullptr;
    SceneManager *sceneManager = nullptr;
    ComponentManager *componentManager = nullptr;
    CameraManager *cameraManager = nullptr;
    std::unordered_map<Entity, TextLines> textLines = {};

  public:
    TextRenderingEntitySystem();
    void OnRegisterEntity(Entity entity) override;
    void OnEntityDestroyed(Entity entity) override;
    void UpdateEntityText(Entity entity, const TextLabelComponent& textLabelComponent);
    void Render() override;
};

#endif //TEXT_RENDERING_ENTITY_SYSTEM_H
