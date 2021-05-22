#pragma once

#include "Engine/Managers/Manager.hpp"
#include <SDL.h>

class WorldManager final : public Manager {
public:
    WorldManager() = default;
    
    enum class WorldState : char {
        STOPPED,
        RUNNING,
        PAUSED
    };
    
    WorldManager::WorldState getWorldState() const;
    
    void handleCollision();
    void setGameState(WorldManager::WorldState worldState);
    virtual void update(float deltaTime) override;
    
    template<typename T> T* get() {
        for(auto& pair : entities) {
            T* object = dynamic_cast<T*>(pair.first);
            if(object != nullptr) {
                return object;
            }
        }
       
        return nullptr;
    }
private:
    WorldState worldState = WorldState::RUNNING;
};
