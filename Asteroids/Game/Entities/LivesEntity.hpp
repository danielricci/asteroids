#pragma once

#include "Engine/Entities/GameEntity.hpp"
#include <SDL.h>
#include <string>

class LivesEntity : public GameEntity {
public:
    LivesEntity();
        
    void addLives(int lives);
    virtual void render(SDL_Renderer& renderer) override;
    void reset();
    virtual void update(const SDL_Event& event) override;
private:
    std::string toString() const;

    int lives = 3;
    const int MAX_LIVES = 99;
};
