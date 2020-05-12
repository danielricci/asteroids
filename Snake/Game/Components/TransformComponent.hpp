/**
* MIT License
*
* Copyright (c) 2020 Daniel Ricci {@literal <thedanny09@icloud.com>}
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#pragma once

#include "Game/Components/Component.hpp"

#include <Eigen/Dense>
#include <SDL.h>

class TransformComponent : public Component {
public:
    TransformComponent(GameObject* gameObject) : Component(gameObject) {
    }
    
    TransformComponent(GameObject* gameObject, int x, int y, int width, int height) : TransformComponent(gameObject) {
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
        positionVector += this->getGameObject()->getComponent<TransformComponent>()->positionVector;
        return positionVector;
    }
    
    Eigen::Vector2f dimensionVector { 0, 0 };
    Eigen::Vector2f positionVector { 0, 0 };
    Eigen::Vector2f velocityVector { 0, 0 };
};
