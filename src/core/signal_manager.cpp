#include "signal_manager.h"

#include "global_dependencies.h"

SignalManager *SignalManager::instance = nullptr;

SignalManager* SignalManager::GetInstance() {
    if (!instance) {
        instance = new SignalManager();
    }
    return instance;
}

void SignalManager::CreateSignal(const Entity entity, const std::string &signalName) {
    if (!DoesEntityHaveSignal(entity, signalName)) {
        Signal newSignal = {
            .name = signalName,
            .sourceEntity = entity,
            .subscribers = {}
        };
        std::map<std::string, Signal> newEntitySignals = { { newSignal.name, newSignal } };
        entitySignals.emplace(entity, newEntitySignals);
    }
}

void SignalManager::SubscribeToSignal(const Entity sourceEntity, const std::string &signalName, const Entity subscriberEntity, const std::string &subscriberFunctionName) {
    CreateSignal(sourceEntity, signalName);
    Signal signalToSubscribeTo = entitySignals[sourceEntity][signalName];
    SignalSubscriber signalSubscriber = {
        .subscribedEntity = subscriberEntity,
        .subscribedFunctionName = subscriberFunctionName
    };
    signalToSubscribeTo.subscribers.emplace(signalSubscriber.subscribedEntity, signalSubscriber);
    entitySignals[sourceEntity][signalName] = signalToSubscribeTo;
}

void SignalManager::EmitSignal(const Entity entity, const std::string &signalName, SignalArguments args) {
    static ScriptEntitySystem *scriptEntitySystem = (ScriptEntitySystem*) GD::GetContainer()->entitySystemManager->GetEntitySystem<ScriptEntitySystem>();
    CreateSignal(entity, signalName);
    Signal signalToEmit = entitySignals[entity][signalName];
    for (auto const &pair : signalToEmit.subscribers) {
        SignalSubscriber signalSubscriber = pair.second;
        scriptEntitySystem->ReceiveSubscribedSignal(
            signalSubscriber.subscribedEntity,
            signalSubscriber.subscribedFunctionName,
            args);
    }
}

void SignalManager::EmitSignal(const Entity entity, const std::string &signalName) {
    EmitSignal(entity, signalName, SignalArguments{});
}

void SignalManager::RemoveEntitySignals(const Entity entity) {
    entitySignals.erase(entity);
}

bool SignalManager::DoesEntityHaveSignal(const Entity entity, const std::string &signalName) {
    if (entitySignals.count(entity) > 0) {
        std::map<std::string, Signal> entitySignalMap = entitySignals[entity];
        if (entitySignalMap.count(signalName) > 0) {
            return true;
        }
    }
    return false;
}
