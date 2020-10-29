#include "Engine/Managers/GameManager.hpp"
#include "Engine/Managers/GameSettingsManager.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Game/Entities/PlayerEntity.hpp"

void GameManager::render(SDL_Renderer& renderer) {
    if(this->gameState == GameState::STARTED) {
        for(Node* node : this->nodes) {
            if(node != nullptr) {
                Entity* entity = dynamic_cast<Entity*>(node);
                if(entity != nullptr) {
                    entity->render(renderer);
                }
            }
        }
    }
}

void GameManager::update(float deltaTime) {
    if(this->gameState == GameState::STARTED) {
        for(Node* node : this->nodes) {
            if(node != nullptr) {
                Entity* entity = dynamic_cast<Entity*>(node);
                if(entity != nullptr) {
                    entity->update(deltaTime);
                }
            }
        }
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
        for(Node* node : this->nodes) {
            if(node != nullptr) {
                Entity* entity = dynamic_cast<Entity*>(node);
                if(entity != nullptr) {
                    entity->update(event);
                }
            }
        }
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
                int width = 0;
                int height = 0;
                ManagerHelper::get<GameSettingsManager>()->getWindowSize(width, height);
                PlayerEntity* playerEntity = new PlayerEntity();
                playerEntity->setPosition({width/2, height/2});
                this->addNode(playerEntity);
            }
            break;
        }
        case GameState::PAUSED: {
            if(oldState == GameState::STARTED) {
                // Need to pause the game world
            }
            break;
        }
    }
}

GameManager::GameState GameManager::getGameState() const {
    return this->gameState;
}
