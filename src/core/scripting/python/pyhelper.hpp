#ifndef PYHELPER_HPP
#define PYHELPER_HPP
#pragma once

#include <Python.h>
#include <iostream>

#include "python_source.h"
#include "python_modules.h"

class CPyInstance {
public:
    CPyInstance() {
        Py_SetProgramName(L"roll_engine_scripting");
//        PyImport_AppendInittab("seika_engine_api", &PyInit_seikaRenderer); // Load engine modules
        Py_Initialize();
        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.path.append(\".\")");

        PyRun_SimpleString(PYTHON_SOURCE_LOAD_SOURCE_IMPORTER_SNIPPET.c_str());
        PyRun_SimpleString(PYTHON_SOURCE_IMPORT_ENGINE_MODULE_SNIPPET.c_str());
    }

    ~CPyInstance() {
        Py_Finalize();
    }

    static void ImportModuleFromString(const std::string &modulePath, const std::string &moduleSource) {
        std::string source =
                "SourceImporter(modules={\n"
                "\"" + modulePath + "\": \"\"\"\n"
                + moduleSource +
                "\"\"\"\n"
                "})\n";
        PyRun_SimpleString(source.c_str());
    }
};

class CPyObject {
private:
    PyObject* pyObj;
public:
    CPyObject(): pyObj(NULL) {}

    CPyObject(PyObject* p) : pyObj(p) {}

    ~CPyObject() {
        Release();
    }

    PyObject* GetObj() {
        return pyObj;
    }

    PyObject* SetObj(PyObject* p) {
        return (pyObj=p);
    }

    PyObject* AddRef() {
        if(pyObj) {
            Py_INCREF(pyObj);
        }
        return pyObj;
    }

    void Release() {
        if(pyObj) {
            Py_DECREF(pyObj);
        }
        pyObj = NULL;
    }

    PyObject* operator ->() {
        return pyObj;
    }

    bool is() {
        return pyObj ? true : false;
    }

    operator PyObject*() {
        return pyObj;
    }

    PyObject* operator = (PyObject* p) {
        pyObj = p;
        return pyObj;
    }
};

class PyHelper {
public:
    static CPyObject CreateModuleEntityInstance(Entity entity, const std::string &classPath, const std::string &className) {
        // Import Module
        CPyObject pName = PyUnicode_FromString(classPath.c_str());
        CPyObject pModule = PyImport_Import(pName);
        assert(pModule != nullptr && "Python module is NULL!");

        // Class
        CPyObject pModuleDict = PyModule_GetDict(pModule);
        CPyObject pClass = PyDict_GetItemString(pModuleDict, className.c_str());
        assert(pClass != nullptr && "Python class is NULL!");

        // Instance
        CPyObject argList = Py_BuildValue("(i)", entity);
        CPyObject pClassInstance = PyObject_CallObject(pClass, argList);
        assert(pClassInstance != nullptr && "Python class instance is NULL!");

        return pClassInstance;
    }
};

#endif //PYHELPER_HPP
