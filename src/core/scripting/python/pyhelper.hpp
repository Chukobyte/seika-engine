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
        PyRun_SimpleString("print(\"hello world!\")");
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

#endif //PYHELPER_HPP
