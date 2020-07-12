#pragma once

#include "Engine/Components/Component.hpp"
#include <Eigen/Dense>
#include <SDL.h>

class TransformComponent : public Component {
public:
    TransformComponent() = default;
            
    SDL_Rect getRectangle() const;
    Eigen::Vector2f getWorldPosition() const;
        
    Eigen::Vector2f dimensionVector { 0, 0 };
    Eigen::Vector2f positionVector { 0, 0 };
    Eigen::Vector2f velocityVector { 0, 0 };
};
