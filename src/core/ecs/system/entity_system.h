#ifndef ENTITY_SYSTEM_H
#define ENTITY_SYSTEM_H

#include <set>

#include "../entity/entity.h"
#include "../../global_dependencies.h"

const unsigned int MAX_SYSTEMS = 32;

class EntitySystem {
  protected:
    bool enabled = false;
  public:
    std::set<Entity> entities;

    bool IsEnabled() {
        return enabled;
    }

    virtual void Initialize() = 0;

    virtual void Enable() {
        enabled = true;
    }

    virtual void Disable() {
        enabled = false;
    }

    // Hooks
    virtual void OnRegisterEntity(Entity entity) {
        entities.insert(entity);
    }
    virtual void OnUnRegisterEntity(Entity entity) {
        entities.erase(entity);
    }

    virtual void OnEntityDestroyed(Entity entity) {}

    // Subscribable hooks
    virtual void Process(float deltaTime) {}
    virtual void PhysicsProcess(float deltaTime) {}
    virtual void Render() {}
};

#endif //ENTITY_SYSTEM_H
