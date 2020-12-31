#include "Engine/Managers/GameManager.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Engine/Managers/WindowManager.hpp"
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
            if(oldState == GameState::STOPPED) {
                SDL_Rect windowSize = ManagerHelper::get<WindowManager>()->getWindowSize();
                PlayerEntity* playerEntity = new PlayerEntity();
                playerEntity->setPosition({windowSize.w/2, windowSize.h/2});
                addEntity(playerEntity);

                AsteroidEntity* a1 = new AsteroidEntity();
                addEntity(a1);
                a1->setPosition({150, 550});
                
                AsteroidEntity* a2 = new AsteroidEntity();
                addEntity(a2);
                a2->setPosition({150, 950});
                
                AsteroidEntity* a3 = new AsteroidEntity();
                addEntity(a3);
                a3->setPosition({950, 550});
                
                AsteroidEntity* a4 = new AsteroidEntity();
                addEntity(a4);
                a4->setPosition({950, 950});
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
