#pragma once

#include "Engine/Managers/Manager.hpp"
#include <SDL.h>

class WorldManager final : public Manager {
public:
    WorldManager() = default;
    
    enum class GameState : char {
        STOPPED,
        RUNNING,
        PAUSED
    };
    
    WorldManager::GameState getGameState() const;
    
    void handleCollision();
    void setGameState(WorldManager::GameState gameState);
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
    GameState gameState = GameState::STOPPED;
};
