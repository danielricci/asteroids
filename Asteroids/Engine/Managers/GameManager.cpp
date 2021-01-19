#include "Engine/Managers/GameManager.hpp"
#include "Game/Entities/AsteroidEntity.hpp"
#include "Game/Entities/PlayerEntity.hpp"
#include "Game/Entities/SaucerEntity.hpp"
#include <Eigen/Dense>

GameManager::GameState GameManager::getGameState() const {
    return this->gameState;
}

void GameManager::handleCollision() {
    for(auto& pair : entities) {
        std::for_each(entities.begin(), entities.end(), [&pair](const auto& thisPair) {
            // It might be too naive to not send collision messages to destroyed entities
            if(pair.first != thisPair.first && pair.second.state != ManagerInformation::State::Destroy && thisPair.second.state != ManagerInformation::State::Destroy) {
                pair.first->collisionCheck(*(thisPair.first));
            }
        });
    }
}

void GameManager::render(SDL_Renderer& renderer) {
    Manager::render(renderer);
    SDL_Color color;
    SDL_GetRenderDrawColor(&renderer, &color.r, &color.g, &color.b, &color.a);
    SDL_SetRenderDrawColor(&renderer, 0xFF, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    std::for_each(entities.begin(), entities.end(), [&renderer](const auto& entityPair) {
        Eigen::Vector2f position = entityPair.first->getPosition();
        SDL_RenderDrawLine(&renderer, position.x(), position.y(), position.x() + 20, position.y());
        SDL_RenderDrawLine(&renderer, position.x(), position.y(), position.x(), position.y() + 20);
    });
    SDL_SetRenderDrawColor(&renderer, color.r, color.g, color.b, color.a);
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
                PlayerEntity* playerEntity = new PlayerEntity();
                playerEntity->setPosition({450, 450});
                addEntity(playerEntity);

                AsteroidEntity* asteroidEntity = new AsteroidEntity();
                addEntity(asteroidEntity);
                asteroidEntity->setPosition({150, 550});
                
//                AsteroidEntity* a2 = new AsteroidEntity();
//                addEntity(a2);
//                a2->setPosition({150, 950});
//                a2->setRotation(-45);
//
//                AsteroidEntity* a3 = new AsteroidEntity();
//                addEntity(a3);
//                a3->setPosition({950, 550});
//                a3->setRotation(-90);
//
//                AsteroidEntity* a4 = new AsteroidEntity();
//                addEntity(a4);
//                a4->setPosition({950, 950});
//                a4->setRotation(-135);
//
//                SaucerEntity* e1 = new SaucerEntity();
//                addEntity(e1);
//                e1->setPosition({40, 450});
//                a4->setRotation(-180);
            }
            break;
        }
        case GameState::PAUSED: {
            break;
        }
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
