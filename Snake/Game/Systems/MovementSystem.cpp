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

#include "Game/Components/CollisionComponent.hpp"
#include "Game/Components/SnakeBodyComponent.hpp"
#include "Game/Components/SnakeInputComponent.hpp"
#include "Game/Systems/MovementSystem.hpp"

#include <Eigen/Dense>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

MovementSystem::MovementSystem(SDL_Window& window) : window(window) {
}

void MovementSystem::process(SnakeObject* snakeObject, FoodObject* foodObject, GameOverObject* gameOverObject) {
    if(snakeObject != nullptr && foodObject != nullptr) {
        SnakeBodyComponent* snakeBodyComponent = snakeObject->getComponent<SnakeBodyComponent>();
                
        // Store a reference of the tail position before performing the move
        // and perform the movement of the snake by a unit
        Eigen::Vector2f tailPosition = snakeBodyComponent->getTail()->positionVector;
        snakeBodyComponent->moveTailToHead();

        // Simulate the mode 2 game by always increasing the snake size
        if(snakeBodyComponent->isGameMode2) {
            snakeBodyComponent->increaseSnakeLength(tailPosition);
        }
        
        int width = 0;
        int height = 0;
        SDL_GetWindowSize(&window, &width, &height);
      
        // The player has won the game
        if(snakeBodyComponent->getLength() == (width / SnakeBodyComponent::CELL_WIDTH) * (height / SnakeBodyComponent::CELL_WIDTH)) {
            std::cout << "YOU WIN!!! :) :) :)" << std::endl;
            gameOverObject->setIsGameOver(true);
        }
        
        // Get the position of the head of the snake
        TransformComponent* snakeHeadTransform = snakeBodyComponent->getHead();
        Eigen::Vector2f snakeHeadWorldPosition = snakeHeadTransform->getWorldPositionVector();
        
        // Test for collision with the outside of the game bounds
        if(snakeHeadWorldPosition.x() < 0 || snakeHeadWorldPosition.y() < 0 || snakeHeadWorldPosition.x() + SnakeBodyComponent::CELL_WIDTH > width || snakeHeadWorldPosition.y() + SnakeBodyComponent::CELL_HEIGHT > height) {
            gameOverObject->setIsGameOver(true);
        }
        // Test for collision with food
        else if(snakeHeadWorldPosition == foodObject->getComponent<TransformComponent>()->positionVector) {
            snakeBodyComponent->increaseSnakeLength(tailPosition);
            processFoodPosition(snakeObject, foodObject);
        }
        // Test for collision with the snake body
        else {
            for(auto snakeBodyTailIterator = snakeBodyComponent->getTailIterator(); snakeBodyTailIterator < snakeBodyComponent->getHeadIterator(); ++snakeBodyTailIterator) {
                TransformComponent* transformComponent = *snakeBodyTailIterator;
                if(transformComponent != snakeBodyComponent->getHead() && transformComponent->getWorldPositionVector() == snakeHeadWorldPosition) {
                    gameOverObject->setIsGameOver(true);
                    break;
                }
            }
        }
    }
}

void MovementSystem::processFoodPosition(SnakeObject* snakeObject, FoodObject* foodObject) {
    
    int width = 0;
    int height = 0;
    SDL_GetWindowSize(&window, &width, &height);

    SnakeBodyComponent* snakeBodyComponent = snakeObject->getComponent<SnakeBodyComponent>();
    std::vector<Eigen::Vector2f> positions;
    for(int i = 0; i < width; i += SnakeBodyComponent::CELL_WIDTH) {
        for(int j = 0; j < height; j += SnakeBodyComponent::CELL_HEIGHT) {
            Eigen::Vector2f position(i, j);
            bool found = false;
            for(auto snakeBodyTailIterator = snakeBodyComponent->getTailIterator(); snakeBodyTailIterator != snakeBodyComponent->getHeadIterator(); ++snakeBodyTailIterator) {
                Eigen::Vector2f snakeBodyWorldPosition = (*snakeBodyTailIterator)->getWorldPositionVector();
                if(snakeBodyWorldPosition.x() == i && snakeBodyWorldPosition.y() == j) {
                    found = true;
                    break;
                }
            }
            if(!found) {
                positions.push_back(position);
            }
        }
    }
    
    if(positions.size() > 0) {
        std::uniform_int_distribution<unsigned long> distribution(0, positions.size() - 1);
        std::mt19937 generator(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
        unsigned long finalIndex = distribution(generator);
        foodObject->getComponent<TransformComponent>()->positionVector = positions[std::fmax(0, std::fmin(finalIndex, positions.size() - 1))];
    }
}
