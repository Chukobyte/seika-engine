#ifndef PYTHON_CACHE_H
#define PYTHON_CACHE_H

#include "../../utils/singleton.h"

#include <map>

#include "pyhelper.hpp"

#include "../../ecs/entity/entity.h"
#include "../../utils/logger.h"

struct CachedPythonModule {
    CPyObject module;
    std::map<std::string, CPyObject> classes;
};

class PythonCache : public Singleton<PythonCache> {
  private:
    static PythonCache *instance;
    std::map<std::string, CachedPythonModule> cache;
    std::map<Entity, CPyObject> activeClassInstances;
  public:
    PythonCache(singleton) {}
    CPyObject GetClass(const std::string &classPath, const std::string &className);
    CPyObject& CreateClassInstance(const std::string &classPath, const std::string &className, Entity entity);
    CPyObject& GetClassInstance(Entity entity);
    bool HasActiveInstance(Entity entity);
    void RemoveClassInstance(Entity entity);

};

#endif //PYTHON_CACHE_H
