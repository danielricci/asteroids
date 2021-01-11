#include "Engine/Managers/GameManager.hpp"
#include "Game/Entities/AsteroidEntity.hpp"
#include "Game/Entities/PlayerEntity.hpp"
#include "Game/Entities/SaucerEntity.hpp"

GameManager::GameState GameManager::getGameState() const {
    return this->gameState;
}

void GameManager::handleCollision() {
    for(auto& pair : entities) {
        std::for_each(entities.begin(), entities.end(), [&pair](const auto& thisPair) {
            if(pair.first != thisPair.first && pair.second.state != ManagerInformation::State::Destroy && thisPair.second.state != ManagerInformation::State::Destroy) {
                pair.first->collision(*(thisPair.first));
            }
        });
    }
}

void GameManager::render(SDL_Renderer& renderer) {
    if(this->gameState == GameState::STARTED) {
        Manager::render(renderer);
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
                PlayerEntity* playerEntity = new PlayerEntity();
                playerEntity->setPosition({450, 450});
                addEntity(playerEntity);

                AsteroidEntity* asteroidEntity = new AsteroidEntity();
                addEntity(asteroidEntity);
                asteroidEntity->setPosition({150, 550});
                asteroidEntity->setRotation(0);
                
                AsteroidEntity* a2 = new AsteroidEntity();
                addEntity(a2);
                a2->setPosition({150, 950});
                a2->setRotation(-45);
                
                AsteroidEntity* a3 = new AsteroidEntity();
                addEntity(a3);
                a3->setPosition({950, 550});
                a3->setRotation(-90);
                
                AsteroidEntity* a4 = new AsteroidEntity();
                addEntity(a4);
                a4->setPosition({950, 950});
                a4->setRotation(-135);
                
                SaucerEntity* e1 = new SaucerEntity();
                addEntity(e1);
                e1->setPosition({40, 450});
                a4->setRotation(-180);
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
