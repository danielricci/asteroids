#pragma once

#include "Engine/Components/Component.hpp"
#include <Eigen/Dense>
#include <SDL.h>

class TransformComponent : public Component {
public:
    TransformComponent() = default;
            
    SDL_Rect toRectangle() const;
    static SDL_Rect toRectangle(const Eigen::Vector2f& positionVector, const Eigen::Vector2f& dimensionVector) {
        SDL_Rect rectangle;
        rectangle.x = positionVector.x();
        rectangle.y = positionVector.y();
        rectangle.w = dimensionVector.x();
        rectangle.h = dimensionVector.y();
        return rectangle;
    }
        
    Eigen::Vector2f dimensionVector { 0, 0 };
    Eigen::Vector2f positionVector { 0, 0 };
    Eigen::Vector2f velocityVector { 0, 0 };
};
