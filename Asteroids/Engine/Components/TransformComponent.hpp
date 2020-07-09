#pragma once

#include "Engine/Components/Component.hpp"

#include <Eigen/Dense>
#include <SDL.h>

class TransformComponent : public Component {
public:
    TransformComponent() = default;
            
    SDL_Rect getRectangle() const {
        SDL_Rect rectangle;
        rectangle.x = positionVector.x();
        rectangle.y = positionVector.y();
        rectangle.w = dimensionVector.x();
        rectangle.h = dimensionVector.y();
        return rectangle;
    }
    
    Eigen::Vector2f getWorldPosition() const {
        
    //    Component* parentComponent = this->getParentNode();
        
        
        //Eigen::Vector2f worldPosition = positionVector;
        
        
        
        
        
        return {0, 0};
    }
        
    Eigen::Vector2f dimensionVector { 0, 0 };
    Eigen::Vector2f positionVector { 0, 0 };
    Eigen::Vector2f velocityVector { 0, 0 };
};
