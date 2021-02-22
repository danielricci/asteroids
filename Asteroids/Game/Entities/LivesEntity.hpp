#pragma once

#include "Engine/Entities/GameEntity.hpp"

class LivesEntity : public GameEntity {
public:
    LivesEntity() = default;
    void reset();
private:
    int lives = 3;
};
