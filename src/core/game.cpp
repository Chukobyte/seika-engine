#include "game.h"
#include "global_dependencies.h"

Game::Game() {
    logger = Logger::GetInstance();
    logger->SetLogLevel(LogLevel_DEBUG);
    engineContext = GD::GetContainer()->engineContext;
}

void Game::Initialize() {
    logger->Debug("Roll Back Engine " + engineContext->GetEngineVersion() + " Started!");
}

void Game::ProcessInput() {}

void Game::Update() {}

void Game::Render() {}

bool Game::IsRunning() {
    return engineContext->IsRunning();
}

void Game::Destroy() {}
