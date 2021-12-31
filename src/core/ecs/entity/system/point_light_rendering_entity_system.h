#ifndef POINT_LIGHT_RENDERING_ENTITY_SYSTEM_H
#define POINT_LIGHT_RENDERING_ENTITY_SYSTEM_H

#include "entity_system.h"
#include "../../component/components/transform3D_component.h"
#include "../../component/components/light3D_component.h"
#include "../../component/components/material_component.h"
#include "../../../math/space_handler.h"

class PointLightRenderingEntitySystem : public EntitySystem {
  private:
    Renderer3D *renderer3D = nullptr;
    ComponentManager *componentManager = nullptr;

  public:

    PointLightRenderingEntitySystem() {
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
                PointLightComponent pointLightComponent = componentManager->GetComponent<PointLightComponent>(entity);
                MaterialComponent materialComponent = componentManager->GetComponent<MaterialComponent>(entity);

                renderer3D->AddPointLightDrawBatch(
                PointLightDrawBatch{
                    .position = transform3DComponent.position,
                    .scale = transform3DComponent.scale,
                    .ambient = materialComponent.ambient,
                    .diffuse = materialComponent.diffuse,
                    .specular = materialComponent.specular,
                    .linear = pointLightComponent.linear,
                    .quadratic = pointLightComponent.quadratic,
                    .constant = pointLightComponent.constant
                });
            }
        }
    }
};

#endif //POINT_LIGHT_RENDERING_ENTITY_SYSTEM_H
