#include "Engine/Managers/GameManager.hpp"
#include "Engine/System/Engine.hpp"
#include "Game/Entities/PlayerEntity.hpp"

void GameManager::render(SDL_Renderer& renderer) {
    if(this->gameState == GameState::STARTED) {
        for(Entity* entity : entities) {
            if(entity != nullptr) {
                entity->render(renderer);
            }
        }
    }
}

void GameManager::update(float deltaTime) {
    if(this->gameState == GameState::STARTED) {
        for(Entity* entity : entities) {
            if(entity != nullptr) {
                entity->update(deltaTime);
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
        for(Entity* entity : entities) {
            if(entity != nullptr) {
                entity->update(event);
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
                SDL_UserEvent userEvent;
                userEvent.type = SDL_USEREVENT;
                userEvent.code = static_cast<int>(Engine::EngineEvents::EVENT_ENGINE_START_GAME);
                SDL_Event event;
                event.type = SDL_USEREVENT;
                event.user = userEvent;
                SDL_PushEvent(&event);
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
