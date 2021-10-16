#ifndef SIGNAL_MANAGER_H
#define SIGNAL_MANAGER_H

#include <string>
#include <map>
#include <vector>

#include "signal_arguments.h"

#include "ecs/entity/entity.h"

#include "utils/logger.h"

struct SignalSubscriber {
    Entity subscribedEntity;
    std::string subscribedFunctionName;
};

struct Signal {
    std::string name;
    Entity sourceEntity;
    std::map<Entity, SignalSubscriber> subscribers;
};

class SignalManager {
  private:
    static SignalManager *instance;
    Logger *logger = nullptr;
    std::map<Entity, std::map<std::string, Signal>> entitySignals;

    SignalManager() {
        this->logger = Logger::GetInstance();
    }
public:
    static SignalManager* GetInstance();

    void CreateSignal(Entity entity, const std::string &signalName);

    void SubscribeToSignal(Entity sourceEntity, const std::string &signalName, Entity subscriberEntity, const std::string &subscriberFunctionName);

    void EmitSignal(Entity entity, const std::string &signalName, SignalArguments args);

    void EmitSignal(Entity entity, const std::string &signalName);

    void RemoveEntitySignals(Entity entity);

    bool DoesEntityHaveSignal(Entity entity, const std::string &signalName);
};


#endif //SIGNAL_MANAGER_H
