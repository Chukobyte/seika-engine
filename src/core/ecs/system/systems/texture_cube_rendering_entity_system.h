#ifndef TEXTURE_CUBE_RENDERING_ENTITY_SYSTEM_H
#define TEXTURE_CUBE_RENDERING_ENTITY_SYSTEM_H

#include "../entity_system.h"
#include "../../component/components/transform3D_component.h"
#include "../../component/components/material_component.h"
#include "../../../math/space_handler.h"

class TextureCubeRenderingEntitySystem : public EntitySystem {
  private:
    Renderer3D *renderer3D = nullptr;
    ComponentManager *componentManager = nullptr;

  public:

    TextureCubeRenderingEntitySystem() {
        renderer3D = GD::GetContainer()->renderer3D;
        componentManager = GD::GetContainer()->componentManager;
        enabled = true;
    }
    void Initialize() override {}
    void Enable() override {}
    void Disable() override {}

    void OnEntityDestroyed(Entity entity) override {}

    void Render() {
        if (IsEnabled()) {
            for (Entity entity : entities) {
                Transform3DComponent transform3DComponent = componentManager->GetComponent<Transform3DComponent>(entity);
                MaterialComponent materialComponent = componentManager->GetComponent<MaterialComponent>(entity);

                renderer3D->AddTextureCubeDrawBatch(TextureCubeDrawBatch{
                    .position = transform3DComponent.position,
                    .scale = transform3DComponent.scale,
                    .rotationAngleInDegrees = transform3DComponent.rotationAngleInDegrees,
                    .rotationAxisInDegrees = transform3DComponent.rotationAxisInDegrees,
                    .diffuseMap = materialComponent.diffuseMap,
                    .specularMap = materialComponent.specularMap,
                    .shininess = materialComponent.shininess
                });
            }
        }
    }
};

#endif //TEXTURE_CUBE_RENDERING_ENTITY_SYSTEM_H
