#ifndef PYTHON_CACHE_H
#define PYTHON_CACHE_H

#include <map>

#include "pyhelper.hpp"

struct CachedPythonModule {
    CPyObject module;
    std::map<std::string, CPyObject> classes;
};

class PythonCache {
  private:
    std::map<std::string, CachedPythonModule> cache;
  public:
    CPyObject GetClassObject(const std::string &classPath, const std::string &className) {
        if (cache.count(classPath) <= 0) {
            CPyObject pName = PyUnicode_FromString(classPath.c_str());
            CPyObject pModule = PyImport_Import(pName);
            assert(pModule != nullptr && "Python module is NULL!");
            std::map<std::string, CPyObject> pClasses;
            cache.emplace(classPath, CachedPythonModule{
                .module = pModule,
                .classes = pClasses
            });
        }
        if (cache[classPath].classes.count(className) <= 0) {
            CPyObject pModuleDict = PyModule_GetDict(cache[classPath].module);
            CPyObject pClass = PyDict_GetItemString(pModuleDict, className.c_str());
            assert(pClass != nullptr && "Python class is NULL!");
            cache[classPath].classes.emplace(className, pClass);
        }
        std::cout << "classPath: " << classPath << ", className: " << className << std::endl;
        return cache[classPath].classes[className];
    }
};

#endif //PYTHON_CACHE_H
