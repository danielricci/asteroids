#include "Engine/Managers/WorldManager.hpp"
#include "Game/Entities/AsteroidEntity.hpp"
#include "Game/Entities/PlayerEntity.hpp"
#include "Game/Entities/SaucerEntity.hpp"

WorldManager::GameState WorldManager::getGameState() const {
    return this->gameState;
}

void WorldManager::handleCollision() {
    for(auto& pair : entities) {
        std::for_each(entities.begin(), entities.end(), [&pair](const auto& thisPair) {
            // It might be naive to not send collision messages to destroyed entities
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

void WorldManager::setGameState(WorldManager::GameState gameState) {
    this->gameState = gameState;
//    switch(gameState) {
//        case GameState::STOPPED: {
//            break;
//        }
//        case GameState::STARTED: {
//            if(oldState == GameState::STOPPED) {
//                addEntity(new PlayerEntity());
//           }
//            break;
//        }
//        case GameState::PAUSED: {
//            break;
//        }
//    }
}

void WorldManager::update(float deltaTime) {
    // TODO fixme
//    if(this->gameState == GameState::STARTED) {
//        Manager::update(deltaTime);
//    }
}
