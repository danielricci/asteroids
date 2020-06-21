#pragma once

#include "Engine/Components/Component.hpp"

#include <Eigen/Dense>
#include <SDL.h>

class TransformComponent : public Component {
public:
    TransformComponent(Entity* entity) : Component(entity) {
    }
    
    TransformComponent(Entity* entity, int x, int y, int width, int height) : TransformComponent(entity) {
        this->positionVector.x() = x;
        this->positionVector.y() = y;
        this->dimensionVector.x() = width;
        this->dimensionVector.y() = height;
    }
        
    SDL_Rect getRectangle() const {
        SDL_Rect rectangle;
        rectangle.x = positionVector.x();
        rectangle.y = positionVector.y();
        rectangle.w = dimensionVector.x();
        rectangle.h = dimensionVector.y();
        return rectangle;
    }
    
    Eigen::Vector2f getWorldPositionVector() {
        // TODO Eventually it will be required to go up the parent chain to gather all positions
        Eigen::Vector2f positionVector = this->positionVector;
        positionVector += this->getEntity()->getComponent<TransformComponent>()->positionVector;
        return positionVector;
    }
    
    Eigen::Vector2f dimensionVector { 0, 0 };
    Eigen::Vector2f positionVector { 0, 0 };
    Eigen::Vector2f velocityVector { 0, 0 };
};
