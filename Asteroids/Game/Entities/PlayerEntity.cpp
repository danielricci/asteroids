#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Game/Entities/PlayerEntity.hpp"
#include "Game/Components/PlayerInputComponent.hpp"
#include <Eigen/Dense>
#include <iostream>
#include <cmath>

PlayerEntity::PlayerEntity() {
    // TODO: this->setDirection(90);
    this->addNode(new ShapeComponent{{0, 0}, {9, 24}, {0, 20}, {-9, 24}, {0, 0}});
    this->addNode(new PlayerInputComponent());
}

void PlayerEntity::render(SDL_Renderer& renderer) {
    this->getNode<ShapeComponent>()->render(renderer);
}

void PlayerEntity::update(const SDL_Event& event) {
    switch(event.type) {
        case SDL_KEYDOWN:
        case SDL_KEYUP: {
            PlayerInputComponent* playerInputComponent = this->getNode<PlayerInputComponent>();
            if(playerInputComponent != nullptr) {
                playerInputComponent->update(event);
            }
            break;
        }
    }
}

void PlayerEntity::update(float deltaTime) {
    PlayerInputComponent* playerInputComponent = this->getNode<PlayerInputComponent>();
    if(playerInputComponent != nullptr) {
        switch(playerInputComponent->getPlayerAction()) {
            case PlayerInputComponent::PlayerAction::NONE: {
                break;
            }
            case PlayerInputComponent::PlayerAction::ROTATE_LEFT: {
                TransformComponent* transformComponent = this->getNode<TransformComponent>();
                Eigen::Vector2f oldPosition = transformComponent->position;
                
                ShapeComponent* shapeComponent = this->getNode<ShapeComponent>();
                
                static int degree = 0;
                degree = (degree + (int)(deltaTime * 360)) % 360;
                double radians = degree * M_PI/180;
                std::cout << degree << std::endl;
                for(int i = 0; i < shapeComponent->getSize(); ++i) {
                    SDL_Point point = (*shapeComponent)[i];
                 
                    int newX = static_cast<int>(std::cos(radians) * point.x - std::sin(radians) * point.y);
                    int newY = static_cast<int>(std::sin(radians) * point.x + std::cos(radians) * point.y);
                    
                    //(*shapeComponent)[i].x = newX;
                    //(*shapeComponent)[i].y = newY;
                }
                
                //this->setPosition(oldPosition);
                break;
            }
            case PlayerInputComponent::PlayerAction::ROTATE_RIGHT: {
                
                break;
            }
        }
    }
}
