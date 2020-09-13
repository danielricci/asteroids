#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Game/Components/PlayerInputComponent.hpp"
#include "Game/Entities/PlayerEntity.hpp"
#include <cmath>
#include <Eigen/Dense>
#include <iostream>

PlayerEntity::PlayerEntity() {
    ShapeComponent* shapeComponent = new ShapeComponent{{0, 0}, {-24, 10}, {-20, 0}, {-24, -10}, {0, 0}};
    shapeComponent->getNode<TransformComponent>()->orientation = -90;
    shapeComponent->getNode<TransformComponent>()->velocity = Eigen::Vector2f(275, 275);
    
    // Offset the position of the shape w.r.t the center of the shape, making the
    // center the actual origin rather than the top-left
    SDL_Point shapeCenterPoint = shapeComponent->getShapeCenter();
    shapeComponent->setOrigin(Eigen::Vector2f(shapeCenterPoint.x, shapeCenterPoint.y));
    for(int i = 0; i < shapeComponent->getSize(); ++i) {
        (*shapeComponent)[i].x += shapeCenterPoint.x;
    }
    this->addNode(shapeComponent);
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
        ShapeComponent* shapeComponent = this->getNode<ShapeComponent>();
        TransformComponent* transformComponent = shapeComponent->getNode<TransformComponent>();
        switch(playerInputComponent->getRotationAction()) {
            case PlayerInputComponent::PlayerAction::NONE: {
                break;
            }
            case PlayerInputComponent::PlayerAction::ROTATE_LEFT: {
                transformComponent->orientation = (static_cast<int>(transformComponent->orientation - (deltaTime * 360)) % 360);
                std::cout << transformComponent->orientation << std::endl;
                break;
            }
            case PlayerInputComponent::PlayerAction::ROTATE_RIGHT: {
                transformComponent->orientation = (static_cast<int>(transformComponent->orientation + (deltaTime * 360)) % 360);
                std::cout << transformComponent->orientation << std::endl;
                break;
            }
            default: {
                break;
            }
        }
        
        switch(playerInputComponent->getThrustAction()) {
            case PlayerInputComponent::PlayerAction::THRUST: {
                ShapeComponent* shapeComponent = this->getNode<ShapeComponent>();
                TransformComponent* transformComponent = shapeComponent->getNode<TransformComponent>();
                double radians = transformComponent->orientation * M_PI / 180;
                
                Eigen::Vector2f position = this->getPosition();
                position.x() += (std::cos(radians) * transformComponent->velocity.x() * deltaTime);
                position.y() += (std::sin(radians) * transformComponent->velocity.y() * deltaTime);
                this->setPosition(position);
                break;
            }
            default: {
                break;
            }
        }
    }
}
