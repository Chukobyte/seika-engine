#ifndef ENTITY_SYSTEM_H
#define ENTITY_SYSTEM_H

#include <set>

#include "../entity/entity_tag_cache.h"
#include "../../global_dependencies.h"

const unsigned int MAX_SYSTEMS = 32;

class EntitySystem {
  public:
    bool IsEnabled() {
        return enabled;
    }

    virtual void Initialize() {}

    virtual void Enable() {
        enabled = true;
    }

    virtual void Disable() {
        enabled = false;
    }

    bool HasEntity(Entity entity) const {
        return entities.count(entity) > 0;
    }

    // Hooks
    virtual void OnRegisterEntity(Entity entity) {
        entities.insert(entity);
    }
    virtual void OnUnRegisterEntity(Entity entity) {
        entities.erase(entity);
    }

    virtual void OnEntityDestroyed(Entity entity) {
        entities.erase(entity);
    }

    // Subscribable hooks
    virtual void Process(float deltaTime) {}
    virtual void PhysicsProcess(float deltaTime) {}
    virtual void Render() {}

    virtual void OnEntityTagsUpdated(Entity entity, const std::vector<std::string>& oldTags, const std::vector<std::string>& newTags) {
        entityTagCache.RemoveEntityTags(entity, oldTags);
        entityTagCache.AddEntityTags(entity, newTags);
    }

    virtual void OnEntityTagsRemoved(Entity entity, const std::vector<std::string>& tags) {
        entityTagCache.RemoveEntityTags(entity, tags);
    }

  protected:
    bool enabled = false;
    EntityTagCache entityTagCache;
    std::set<Entity> entities;
};

#endif //ENTITY_SYSTEM_H
