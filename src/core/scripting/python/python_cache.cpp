#include "python_cache.h"

CPyObject PythonCache::GetClass(const std::string &classPath, const std::string &className) {
    if (cache.count(classPath) <= 0) {
        CPyObject pName = PyUnicode_FromString(classPath.c_str());
        CPyObject pModule = PyImport_Import(pName);
        // Fail over to internal import
        if (pModule == nullptr) {
            CPyObject fromListObject = PyUnicode_FromString("[*]");
            pModule = PyImport_ImportModuleEx(classPath.c_str(), nullptr, nullptr, fromListObject);
            PyErr_Print();
        }
        assert(pModule != nullptr && "Python module is NULL!");
        pModule.AddRef();
        std::map<std::string, CPyObject> pClasses;
        cache.emplace(classPath, CachedPythonModule{
            .module = pModule,
            .classes = pClasses
        });
    }
    if (cache[classPath].classes.count(className) <= 0) {
        CPyObject pModuleDict = PyModule_GetDict(cache[classPath].module);
        assert(pModuleDict != nullptr && "Python module dict is NULL!");
        CPyObject pClass = PyDict_GetItemString(pModuleDict, className.c_str());
        assert(pClass != nullptr && "Python class is NULL!");
        cache[classPath].classes.emplace(className, pClass);
    }
    return cache[classPath].classes[className];
}

CPyObject& PythonCache::CreateClassInstance(const std::string &classPath, const std::string &className, Entity entity) {
    CPyObject argList = Py_BuildValue("(i)", entity);
    CPyObject classRef = GetClass(classPath, className);
    assert(classRef != nullptr && "Error with getting cached python class info!");
    CPyObject pClassInstance = PyObject_CallObject(classRef, argList);
    assert(pClassInstance != nullptr && "Python class instance is NULL on creation!");
    activeClassInstances.emplace(entity, pClassInstance);
    activeClassInstances[entity].AddRef();
    activeClassInstances[entity].AddRef();
    return activeClassInstances[entity];
}

CPyObject& PythonCache::GetClassInstance(Entity entity) {
    assert(HasActiveInstance(entity) && "Entity not active!");
    return activeClassInstances[entity];
}

bool PythonCache::HasActiveInstance(Entity entity) {
    return activeClassInstances.count(entity) > 0;
}

void PythonCache::RemoveClassInstance(Entity entity) {
    activeClassInstances[entity].Release();
    activeClassInstances.erase(entity);
}
