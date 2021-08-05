#ifndef SPOT_LIGHT_RENDERING_ENTITY_SYSTEM_H
#define SPOT_LIGHT_RENDERING_ENTITY_SYSTEM_H

#include "entity_system.h"
#include "../../component/components/transform3D_component.h"
#include "../../component/components/light3D_component.h"
#include "../../component/components/material_component.h"
#include "../../../math/space_handler.h"

class SpotLightRenderingEntitySystem : public EntitySystem {
  private:
    Renderer3D *renderer3D = nullptr;
    ComponentManager *componentManager = nullptr;

  public:

    SpotLightRenderingEntitySystem() {
        renderer3D = GD::GetContainer()->renderer3D;
        componentManager = GD::GetContainer()->componentManager;
        enabled = true;
    }
    void Initialize() override {}
    void Enable() override {}
    void Disable() override {}

    void UnregisterEntity(Entity entity) override {}

    void Render() {
        if (IsEnabled()) {
            for (Entity entity : entities) {
                Transform3DComponent transform3DComponent = componentManager->GetComponent<Transform3DComponent>(entity);
                SpotLightComponent spotLightComponent = componentManager->GetComponent<SpotLightComponent>(entity);
                MaterialComponent materialComponent = componentManager->GetComponent<MaterialComponent>(entity);

                renderer3D->AddSpotLightDrawBatch(
                SpotLightDrawBatch{
                    .isAttachedToCamera = spotLightComponent.isAttachedToCamera,
                    .position = transform3DComponent.position,
                    .direction = spotLightComponent.direction,
                    .ambient = materialComponent.ambient,
                    .diffuse = materialComponent.diffuse,
                    .specular = materialComponent.specular,
                    .linear = spotLightComponent.linear,
                    .quadratic = spotLightComponent.quadratic,
                    .constant = spotLightComponent.constant,
                    .cutoff = spotLightComponent.cutoffInDegrees,
                    .outerCutoff = spotLightComponent.outerCutoffInDegrees
                });
            }
        }
    }
};

#endif //SPOT_LIGHT_RENDERING_ENTITY_SYSTEM_H
