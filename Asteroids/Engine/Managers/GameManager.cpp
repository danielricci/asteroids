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
            if(pair.first != thisPair.first &&
               pair.second.state != ManagerInformation::State::Destroy &&
               pair.second.state != ManagerInformation::State::Disabled &&
               thisPair.second.state != ManagerInformation::State::Destroy &&
               thisPair.second.state != ManagerInformation::State::Disabled) {
                // TODO: Instead of doing this cast, see if there is a way to change the type of the game entity at runtime (templates, generics, etc)
                GameEntity* gameEntityFirst = dynamic_cast<GameEntity*>(pair.first);
                GameEntity* gameEntitySecond = dynamic_cast<GameEntity*>(thisPair.first);
                if(gameEntityFirst != nullptr && gameEntitySecond != nullptr) {
                    gameEntityFirst->collisionCheck(*gameEntitySecond);
                }
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
                addEntity(playerEntity);
                
                AsteroidEntity* asteroidEntity = new AsteroidEntity();
                asteroidEntity->setPosition({40, 550});
                addEntity(asteroidEntity);
                
                SaucerEntity* saucerEntityLarge = new SaucerEntity(SaucerEntity::SaucerType::SAUCER_LARGE);
                saucerEntityLarge->setPosition({40, 350});
                addEntity(saucerEntityLarge);
    
                SaucerEntity* saucerEntitySmall = new SaucerEntity(SaucerEntity::SaucerType::SAUCER_SMALL);
                saucerEntitySmall->setPosition({40, 250});
                addEntity(saucerEntitySmall);
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
    switch(event.type) {
        case SDL_KEYUP: {
            if(event.key.keysym.sym == SDLK_ESCAPE) {
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
            break;
        }
        default: {
            Manager::update(event);
            break;
        }
    }
}
