#include <catch.hpp>
#include "../../core/global_dependencies.h"
#include "../../core/ecs/component/components/transform2D_component.h"

TEST_CASE("Entity Component Orchestrator Tests", "[entity_component_orchestrator]") {
    GD *globalDependencies = GD::GetContainer();
    EntityComponentOrchestrator *entityComponentOrchestrator = globalDependencies->entityComponentOrchestrator;
    SECTION("Create Entity") {
        Entity entity1 = entityComponentOrchestrator->CreateEntity();
        Entity entity2 = entityComponentOrchestrator->CreateEntity();

        REQUIRE(entity1 == 1);
        REQUIRE(entity2 == 2);
    }

    SECTION("Destroy Entity") {
        Entity entity = entityComponentOrchestrator->CreateEntity();

        REQUIRE(entityComponentOrchestrator->GetAliveEntityCount() == 1);

        entityComponentOrchestrator->DestroyEntity(entity);

        REQUIRE(entityComponentOrchestrator->GetAliveEntityCount() == 0);
    }

    SECTION("Add Component to Entity") {
        entityComponentOrchestrator->RegisterComponent<Transform2DComponent>();

        Entity entity = entityComponentOrchestrator->CreateEntity();

        Transform2DComponent transform2DComponent;
        entityComponentOrchestrator->AddComponent<Transform2DComponent>(entity, transform2DComponent);

        REQUIRE(entityComponentOrchestrator->HasComponent<Transform2DComponent>(entity));

    }

    globalDependencies->ResetDependencies();
}
