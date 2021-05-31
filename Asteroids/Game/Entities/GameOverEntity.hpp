#pragma once

#include "Engine/System/Event.hpp"
#include "Engine/System/EventArgs.hpp"
#include "Game/Entities/GameEntity.hpp"
#include "SDL.h"

class GameOverEntity : public GameEntity {
public:
    GameOverEntity();

    bool getIsGameOver() const { return isGameOver; }
    virtual void update(const SDL_Event& event) override;
    Event<EventArgs> eventOnConfirmation;
    void reset();
    
private:
    bool isGameOver = false;
};
