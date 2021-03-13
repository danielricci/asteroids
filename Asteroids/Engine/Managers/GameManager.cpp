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
            // It might be too naive to not send collision messages to destroyed entities
            if(pair.first != thisPair.first && pair.second.state != ManagerInformation::State::Destroy && thisPair.second.state != ManagerInformation::State::Destroy) {
                pair.first->collisionCheck(*(thisPair.first));
            }
        });
    }
}

void GameManager::render(SDL_Renderer& renderer) {
    Manager::render(renderer);
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
                playerEntity->setPosition({450, 150});
                addEntity(playerEntity);

                AsteroidEntity* asteroidEntity = new AsteroidEntity();
                asteroidEntity->setPosition({750, 550});
                addEntity(asteroidEntity);
//
//                AsteroidEntity* a2 = new AsteroidEntity();
//                a2->setOrientation(-45);
//                a2->setPosition({150, 950});
//                addEntity(a2);
//
//                AsteroidEntity* a3 = new AsteroidEntity();
//                a3->setOrientation(-90);
//                a3->setPosition({950, 550});
//                addEntity(a3);
//
//                AsteroidEntity* a4 = new AsteroidEntity();
//                a4->setOrientation(-135);
//                a4->setPosition({950, 950});
//                addEntity(a4);
                
                SaucerEntity* e1 = new SaucerEntity();
                e1->setPosition({40, 350});
                addEntity(e1);
                
                SaucerEntity* e2 = new SaucerEntity();
                e2->setPosition({70, 450});
                addEntity(e2);
                
                SaucerEntity* e3 = new SaucerEntity();
                e3->setPosition({100, 550});
                addEntity(e3);
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
    Manager::update(event);
//    switch(event.type) {
//        case SDL_USEREVENT: {
//
//            break;
//        }
//        case SDL_KEYUP: {
//            if(event.key.keysym.sym == SDLK_ESCAPE) {
//                switch(gameState) {
//                    case GameState::STARTED: {
//                        this->setGameState(GameManager::GameState::PAUSED);
//                        break;
//                    }
//                    case GameState::PAUSED: {
//                        this->setGameState(GameManager::GameState::STARTED);
//                        break;
//                    }
//                    case GameState::STOPPED: {
//                        SDL_Event event;
//                        event.type = SDL_QUIT;
//                        SDL_PushEvent(&event);
//                        break;
//                    }
//                }
//            }
//
//            if(this->gameState == GameState::STARTED) {
//                Manager::update(event);
//            }
//            break;
//        }
//    }
}
