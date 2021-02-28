#pragma once

#include "Engine/Entities/GameEntity.hpp"
#include <SDL.h>
#include <string>

class LivesEntity : public GameEntity {
public:
    LivesEntity();
        
    void addLives(int lives);
    void reset();
    virtual void update(const SDL_Event& event) override;
private:
    std::string toString() const;

    int lives = 0;
    const int MAX_LIVES = 99;
    const int PRECISION = 6;
    const Eigen::Vector2f INDEX_OFFSET_POSITION = Eigen::Vector2f(-20, 0);
};
