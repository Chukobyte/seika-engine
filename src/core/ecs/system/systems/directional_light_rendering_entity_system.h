#ifndef DIRECTIONAL_LIGHT_RENDERING_ENTITY_SYSTEM_H
#define DIRECTIONAL_LIGHT_RENDERING_ENTITY_SYSTEM_H

#include "../entity_system.h"
#include "../../component/components/light3D_component.h"
#include "../../component/components/material_component.h"
#include "../../../math/space_handler.h"

class DirectionalLightRenderingEntitySystem : public EntitySystem {
  private:
    Renderer3D *renderer3D = nullptr;
    ComponentManager *componentManager = nullptr;

  public:

    DirectionalLightRenderingEntitySystem() {
        renderer3D = GD::GetContainer()->renderer3D;
        componentManager = GD::GetContainer()->componentManager;
        enabled = true;
    }

    void Render() override {
        if (IsEnabled()) {
            for (Entity entity : entities) {
                DirectionalLightComponent directionalLightComponent = componentManager->GetComponent<DirectionalLightComponent>(entity);
                MaterialComponent materialComponent = componentManager->GetComponent<MaterialComponent>(entity);

                renderer3D->AddDirectionalLightDrawBatch(
                DirectionalLightDrawBatch{
                    .direction = directionalLightComponent.direction,
                    .ambient = materialComponent.ambient,
                    .diffuse = materialComponent.diffuse,
                    .specular = materialComponent.specular
                });
            }
        }
    }
};

#endif //DIRECTIONAL_LIGHT_RENDERING_ENTITY_SYSTEM_H
