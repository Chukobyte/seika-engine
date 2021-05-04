#include <catch.hpp>

#include "../../core/ecs/entity/entity.h"
#include "../../core/scripting/python/pyhelper.hpp"

TEST_CASE("Python Tests", "[python_test]") {
    CPyInstance *pyInstance = new CPyInstance();
    SECTION("Node Class Test") {
        Entity entity = 1;
        CPyObject classInstance = PyHelper::CreateModuleEntityInstance(entity, "src.test.resources.python.test_node", "TestNode");
        classInstance.AddRef();

        CPyObject pStartFunctionName = PyUnicode_FromString("_start");

        REQUIRE(PyObject_HasAttr(classInstance, pStartFunctionName));

        CPyObject pStartCallValue = PyObject_CallMethod(classInstance, "_start", nullptr);

        CPyObject pPhysicsProcessFunctionName = PyUnicode_FromString("_physics_process");

        REQUIRE(PyObject_HasAttr(classInstance, pPhysicsProcessFunctionName));

        CPyObject pPhysicsProcessCallValue = PyObject_CallMethod(classInstance, "_physics_process", "(f)", 0.01f);
    }
}
