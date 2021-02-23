#pragma once

#include "Engine/Entities/GameEntity.hpp"
#include <SDL.h>

class LivesEntity : public GameEntity {
public:
    LivesEntity();
        
    void decrement();
    void increment();
    virtual void render(SDL_Renderer& renderer) override;
    void reset();
    virtual void update(const SDL_Event& event) override;
private:
    int lives = 3;
    const int MAX_LIVES = 99;
};
