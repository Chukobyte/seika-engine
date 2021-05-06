#include <catch.hpp>

#include "../../core/ecs/entity/entity.h"
#include "../../core/scripting/python/python_cache.h"

TEST_CASE("Python Tests", "[python_test]") {
    CPyInstance *pyInstance = new CPyInstance();
    PythonCache *pythonCache = new PythonCache();
    SECTION("Node Class Test") {
        Entity entity = 1;
        CPyObject pClass = pythonCache->GetClassObject("src.test.resources.python.test_node", "TestNode");
        CPyObject argList = Py_BuildValue("(i)", entity);
        CPyObject classInstance = PyObject_CallObject(pClass, argList);
        classInstance.AddRef();

        CPyObject pStartFunctionName = PyUnicode_FromString("_start");

        REQUIRE(PyObject_HasAttr(classInstance, pStartFunctionName));

        CPyObject pStartCallValue = PyObject_CallMethod(classInstance, "_start", nullptr);

        CPyObject pPhysicsProcessFunctionName = PyUnicode_FromString("_physics_process");

        REQUIRE(PyObject_HasAttr(classInstance, pPhysicsProcessFunctionName));

        CPyObject pPhysicsProcessCallValue = PyObject_CallMethod(classInstance, "_physics_process", "(f)", 0.01f);
    }
}
