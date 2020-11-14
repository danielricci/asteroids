#include "Engine/Managers/GameManager.hpp"
#include "Engine/Managers/GameSettingsManager.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Game/Entities/AsteroidEntity.hpp"
#include "Game/Entities/PlayerEntity.hpp"

void GameManager::render(SDL_Renderer& renderer) {
    if(this->gameState == GameState::STARTED) {
        Manager::render(renderer);
    }
}

void GameManager::update(float deltaTime) {
    if(this->gameState == GameState::STARTED) {
        Manager::update(deltaTime);
    }
}

void GameManager::update(const SDL_Event& event) {
    if(event.key.keysym.sym == SDLK_ESCAPE && event.type == SDL_KEYUP) {
        switch(gameState) {
            case GameState::STARTED: {
                this->setGameState(GameManager::GameState::PAUSED);
                break;
            }
            case GameState::PAUSED: {
                this->setGameState(GameManager::GameState::STARTED);
                break;
            }
            case GameState::STOPPED: {
                SDL_Event event;
                event.type = SDL_QUIT;
                SDL_PushEvent(&event);
                break;
            }
        }
    }
    
    if(this->gameState == GameState::STARTED) {
        Manager::update(event);
    }
}

void GameManager::setGameState(GameManager::GameState gameState) {
    GameManager::GameState oldState = this->gameState;
    this->gameState = gameState;
    
    switch(gameState) {
        case GameState::STOPPED: {
            break;
        }
        case GameState::STARTED: {
            // TODO: Gameplay related code should not be here!
            if(oldState == GameState::STOPPED) {
                int width = 0;
                int height = 0;
                ManagerHelper::get<GameSettingsManager>()->getWindowSize(width, height);
                PlayerEntity* playerEntity = new PlayerEntity();
                playerEntity->setPosition({width/2, height/2});
                this->addNode(playerEntity);
                
                AsteroidEntity* a1 = new AsteroidEntity();
                a1->setPosition({100, 100});
                a1->setAsteroidSize(AsteroidEntity::AsteroidSize::BIG);
                this->addNode(a1);
                
                AsteroidEntity* a2 = new AsteroidEntity();
                a2->setPosition({500, 100});
                a2->setAsteroidSize(AsteroidEntity::AsteroidSize::SMALL);
                this->addNode(a2);
            }
            break;
        }
        case GameState::PAUSED: {
            break;
        }
    }
}

GameManager::GameState GameManager::getGameState() const {
    return this->gameState;
}
