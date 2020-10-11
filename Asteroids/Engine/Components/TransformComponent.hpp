#pragma once

#include "Engine/Components/Component.hpp"
#include <Eigen/Dense>
#include <SDL.h>

class TransformComponent final : public Component {
public:
    TransformComponent() = default;
            
    SDL_Rect toRectangle() const;
    static SDL_Rect toRectangle(const Eigen::Vector2f& position, const Eigen::Vector2f& dimension) {
        SDL_Rect rectangle;
        rectangle.x = position.x();
        rectangle.y = position.y();
        rectangle.w = dimension.x();
        rectangle.h = dimension.y();
        return rectangle;
    }
    
    static const int ORIENTATION_EAST = 0;
    static const int ORIENTATION_NORTH = -90;
    static const int ORIENTATION_WEST = -180;
    static const int ORIENTATION_SOUTH = -270;
    
    static float toRadians(float degrees) {
        return degrees * M_PI/180;
    }
    
    int orientation = 0;
    Eigen::Vector2f origin { 0, 0 };
    Eigen::Vector2f dimension { 0, 0 };
    Eigen::Vector2f position { 0, 0 };
    Eigen::Vector2f velocity { 0, 0 };
};
