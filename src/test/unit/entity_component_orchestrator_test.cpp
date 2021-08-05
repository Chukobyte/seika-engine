#include <catch.hpp>
#include "../../core/global_dependencies.h"
#include "../../core/ecs/component/components/transform2D_component.h"
#include "../../core/ecs/component/components/sprite_component.h"
#include "../../core/ecs/entity/system/sprite_rendering_entity_system.h"

TEST_CASE("Entity Component Orchestrator Tests - Entity", "[entity_component_orchestrator]") {
    GD *globalDependencies = GD::GetContainer();
    EntityComponentOrchestrator *entityComponentOrchestrator = globalDependencies->entityComponentOrchestrator;

    SECTION("Create Entity") {
        Entity entity1 = entityComponentOrchestrator->CreateEntity();
        Entity entity2 = entityComponentOrchestrator->CreateEntity();

        REQUIRE(entity1 == 1);
        REQUIRE(entity2 == 2);
    }

//    SECTION("Destroy Entity") {
//        Entity entity = entityComponentOrchestrator->CreateEntity();
//
//        REQUIRE(entityComponentOrchestrator->GetAliveEntityCount() == 1);
//
//        entityComponentOrchestrator->DestroyEntity(entity);
//
//        REQUIRE(entityComponentOrchestrator->GetAliveEntityCount() == 0);
//    }

    SECTION("Add Component to Entity") {
        entityComponentOrchestrator->RegisterComponent<Transform2DComponent>();

        Entity entity = entityComponentOrchestrator->CreateEntity();

        Transform2DComponent transform2DComponent;
        entityComponentOrchestrator->AddComponent<Transform2DComponent>(entity, transform2DComponent);

        REQUIRE(entityComponentOrchestrator->HasComponent<Transform2DComponent>(entity));
    }

    SECTION("Remove Component from Entity") {
        entityComponentOrchestrator->RegisterComponent<Transform2DComponent>();

        Entity entity = entityComponentOrchestrator->CreateEntity();

        Transform2DComponent transform2DComponent;
        entityComponentOrchestrator->AddComponent<Transform2DComponent>(entity, transform2DComponent);

        REQUIRE(entityComponentOrchestrator->HasComponent<Transform2DComponent>(entity));

        entityComponentOrchestrator->RemoveComponent<Transform2DComponent>(entity);

        REQUIRE(!entityComponentOrchestrator->HasComponent<Transform2DComponent>(entity));
    }

    globalDependencies->ResetDependencies();
}

TEST_CASE("Entity Component Orchestrator Tests - System", "[entity_component_orchestrator]") {
    GD *globalDependencies = GD::GetContainer();
    EntityComponentOrchestrator *entityComponentOrchestrator = globalDependencies->entityComponentOrchestrator;

    SECTION("Register System") {
        entityComponentOrchestrator->RegisterComponent<Transform2DComponent>();
        entityComponentOrchestrator->RegisterSystem<SpriteRenderingEntitySystem>();

        REQUIRE(entityComponentOrchestrator->HasSystem<SpriteRenderingEntitySystem>());
    }

    SECTION("Test if Signature is a valid System Signature") {
        entityComponentOrchestrator->RegisterComponent<Transform2DComponent>();
        entityComponentOrchestrator->RegisterComponent<SpriteComponent>();
        entityComponentOrchestrator->RegisterSystem<SpriteRenderingEntitySystem>();

        REQUIRE(entityComponentOrchestrator->HasSystem<SpriteRenderingEntitySystem>());

        ComponentSignature spriteRenderingSystemSignature;
        spriteRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<Transform2DComponent>(), true);
        spriteRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<SpriteComponent>(), true);

        entityComponentOrchestrator->SetSystemSignature<SpriteRenderingEntitySystem>(spriteRenderingSystemSignature);

        REQUIRE((spriteRenderingSystemSignature & entityComponentOrchestrator->GetSystemSignature<SpriteRenderingEntitySystem>()) == entityComponentOrchestrator->GetSystemSignature<SpriteRenderingEntitySystem>());
    }

    SECTION("Test if Signature is an invalid System Signature") {
        entityComponentOrchestrator->RegisterComponent<Transform2DComponent>();
        entityComponentOrchestrator->RegisterComponent<SpriteComponent>();
        entityComponentOrchestrator->RegisterSystem<SpriteRenderingEntitySystem>();

        REQUIRE(entityComponentOrchestrator->HasSystem<SpriteRenderingEntitySystem>());

        ComponentSignature spriteRenderingSystemSignature;
        spriteRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<Transform2DComponent>(), true);
        spriteRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<SpriteComponent>(), true);

        entityComponentOrchestrator->SetSystemSignature<SpriteRenderingEntitySystem>(spriteRenderingSystemSignature);

        ComponentSignature randomSystemSignature;
        randomSystemSignature.set(entityComponentOrchestrator->GetComponentType<Transform2DComponent>(), true);

        REQUIRE((randomSystemSignature & entityComponentOrchestrator->GetSystemSignature<SpriteRenderingEntitySystem>()) != entityComponentOrchestrator->GetSystemSignature<SpriteRenderingEntitySystem>());
    }

    globalDependencies->ResetDependencies();
}

//TEST_CASE("Entity Component Orchestrator Tests - Scene", "[entity_component_orchestrator]") {
//    GD *globalDependencies = GD::GetContainer();
//    EntityComponentOrchestrator *entityComponentOrchestrator = globalDependencies->entityComponentOrchestrator;

//    SECTION("Change Scene To Root Entity Scene & Delete Test") {
//
//        Entity rootSceneEntity = entityComponentOrchestrator->CreateEntity();
//
//        REQUIRE(!entityComponentOrchestrator->IsEntityInCurrentScene(rootSceneEntity));
//
//        entityComponentOrchestrator->ChangeSceneTo(rootSceneEntity);
//
//        REQUIRE(entityComponentOrchestrator->IsEntityInCurrentScene(rootSceneEntity));
//
//        entityComponentOrchestrator->DestroyEntity(rootSceneEntity);
//
//        REQUIRE(!entityComponentOrchestrator->IsEntityInCurrentScene(rootSceneEntity));
//    }

//    SECTION("Parent Child Relation Test") {
//        Entity parentEntity = entityComponentOrchestrator->CreateEntity();
//        entityComponentOrchestrator->ChangeSceneTo(parentEntity);
//
//        Entity childEntity = entityComponentOrchestrator->CreateEntity();
//        entityComponentOrchestrator->AddChildToEntityScene(parentEntity, childEntity);
//
//        REQUIRE(entityComponentOrchestrator->GetSceneNodeParent(childEntity) == parentEntity);
//    }

//    globalDependencies->ResetDependencies();
//}
