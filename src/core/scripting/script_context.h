#pragma once

#include "../ecs/entity/entity.h"
#include "../signal_arguments.h"

class ScriptContext {
  public:
    virtual ~ScriptContext() = default;
    virtual void Initialize() = 0;
    virtual void CreateEntityInstance(Entity entity) = 0;
    virtual void DeleteEntityInstance(Entity entity) = 0;
    virtual void CallStartOnEntityInstance(Entity entity) = 0;
    virtual void Process(Entity entity, double deltaTime) = 0;
    virtual void PhysicsProcess(Entity entity, double deltaTime) = 0;
    virtual void FlushStdOutBuffer() = 0;
    virtual void ReceiveSubscribedSignal(Entity subscriberEntity, const std::string &subscriberFunctionName, SignalArguments args) = 0;
    virtual bool EntityHasProcessFunction(Entity entity) = 0;
    virtual bool EntityHasPhysicsProcessFunction(Entity entity) = 0;
    virtual void Destroy() = 0;
};
