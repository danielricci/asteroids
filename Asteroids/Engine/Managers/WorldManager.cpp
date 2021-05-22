#include "Engine/Managers/WorldManager.hpp"
#include "Game/Entities/GameEntity.hpp"

WorldManager::WorldState WorldManager::getWorldState() const {
    return this->worldState;
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

void WorldManager::setGameState(WorldManager::WorldState worldState) {
    this->worldState = worldState;
}

void WorldManager::update(float deltaTime) {
    if(this->worldState == WorldState::RUNNING) {
        Manager::update(deltaTime);
    }
}

void WorldManager::update(const SDL_Event& event) {
    if(this->worldState == WorldState::RUNNING) {
        Manager::update(event);
    }
}
