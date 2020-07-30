#include "Engine/Managers/GameManager.hpp"
#include <iostream>

void GameManager::render(SDL_Renderer& renderer) {
}

void GameManager::update(float deltaTime) {

}

void GameManager::update(const SDL_Event& event) {
    if(event.key.keysym.sym == SDLK_ESCAPE && event.type == SDL_KEYUP) {
        switch(gameState) {
            case GameState::STARTED: {
                this->pauseGame();
                break;
            }
            case GameState::PAUSED: {
                this->startGame();
                break;
            }
            case GameState::STOPPED: {
                // No implementation as of yet
                break;
            }
            default: {
                std::cout << "GameManager::update not properly handling gameState = " << static_cast<int>(gameState) << std::endl;
            }
        }
    }
}

void GameManager::stopGame() {
    this->gameState = GameState::STOPPED;
}

bool GameManager::isGameStopped() const {
    return this->gameState == GameState::STOPPED;
}

void GameManager::pauseGame() {
    this->gameState = GameState::PAUSED;
}

bool GameManager::isGamePaused() const {
    return this->gameState == GameState::PAUSED;
}

void GameManager::startGame() {
    this->gameState = GameState::STARTED;
}

bool GameManager::isGameStarted() const {
    return this->gameState == GameState::STARTED;
}
