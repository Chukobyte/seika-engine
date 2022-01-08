#pragma once

#include <set>
#include <unordered_map>

#include "entity.h"

class EntityTagCache {
  public:
    void AddEntityTags(Entity entity, const std::vector<std::string> tags) {
        for (const std::string& tag : tags) {
            if (!HasTag(tag)) {
                entityTagCache.emplace(tag, std::set<Entity> {});
            }
            entityTagCache[tag].insert(entity);
        }
    }

    void RemoveEntityTags(Entity entity, const std::vector<std::string> tags) {
        for (const std::string& tag : tags) {
            if (HasTag(tag)) {
                entityTagCache[tag].erase(entity);
            }
        }
    }

    bool HasTag(const std::string& tag) {
        return entityTagCache.count(tag) > 0;
    }

    std::set<Entity> GetTaggedEntities(const std::string& tag) {
        if (HasTag(tag)) {
            return entityTagCache[tag];
        }
        return {};
    }
  private:
    std::unordered_map<std::string, std::set<Entity>> entityTagCache = {};
};
