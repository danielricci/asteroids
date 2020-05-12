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

#include "Game/Components/SnakeBodyComponent.hpp"
#include "Game/Components/SnakeInputComponent.hpp"

const int SnakeBodyComponent::CELL_WIDTH = 9;
const int SnakeBodyComponent::CELL_HEIGHT = 9;
const int SnakeBodyComponent::INITIAL_LENGTH = 12;

SnakeBodyComponent::SnakeBodyComponent(GameObject* gameObject) : Component(gameObject) {
    for(int i = 0; i < INITIAL_LENGTH; ++i) {
        snakeBody.push_back(new TransformComponent(gameObject, i * CELL_WIDTH, 0, CELL_WIDTH, CELL_HEIGHT));
    }
}

SnakeBodyComponent::~SnakeBodyComponent() {
    for(TransformComponent* transformComponent : snakeBody) {
        delete transformComponent;
        transformComponent = nullptr;
    }
    snakeBody.clear();
}

void SnakeBodyComponent::increaseSnakeLength(const Eigen::Vector2f& position) {
    snakeBody.push_front(new TransformComponent(getGameObject(), position.x(), position.y(), CELL_WIDTH, CELL_HEIGHT));
}

void SnakeBodyComponent::moveTailToHead() {
    // Update the velocity vector of the snake
    SnakeInputComponent* snakeInputComponent = getGameObject()->getComponent<SnakeInputComponent>();
    getGameObject()->getComponent<TransformComponent>()->velocityVector = snakeInputComponent->getInputVector();
    
    // Apply the velocity to a new movement unit
    getTail()->positionVector.x() = getHead()->positionVector.x() + (snakeInputComponent->getInputVector().x() * SnakeBodyComponent::CELL_WIDTH);
    getTail()->positionVector.y() = getHead()->positionVector.y() + (snakeInputComponent->getInputVector().y() * SnakeBodyComponent::CELL_HEIGHT);
    
    // Poition the tail of the snake as the new head of the snake
    snakeBody.push_back(snakeBody.front());
    snakeBody.pop_front();
}
