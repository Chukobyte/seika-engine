#ifndef SCRIPT_CONTEXT_H
#define SCRIPT_CONTEXT_H

#include "../ecs/entity/entity.h"
#include "../signal.h"

class ScriptContext {
  public:
    virtual ~ScriptContext() = default;
    virtual Initialize() = 0;
    virtual CreateEntityInstance(Entity entity) = 0;
    virtual DeleteEntityInstance(Entity entity) = 0;
    virtual void PhysicsProcess(Entity entity, double deltaTime) = 0;
    virtual void ReceiveSubscribedSignal(Entity subscriberEntity, const std::string &subscriberFunctionName, SignalArguments args) = 0;
    virtual void Destroy() = 0;
};

#endif //SCRIPT_CONTEXT_H
