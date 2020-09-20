#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Engine/Managers/GameSettingsManager.hpp"
#include "Game/Components/PlayerInputComponent.hpp"
#include "Game/Entities/PlayerEntity.hpp"
#include <cmath>
#include <random>

PlayerEntity::PlayerEntity() {
    ShapeComponent* shapeComponent = new ShapeComponent{{0, 0}, {-24, 10}, {-20, 0}, {-24, -10}, {0, 0}};
    shapeComponent->getNode<TransformComponent>()->orientation = TransformComponent::ORIENTATION_NORTH;
    
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
        TransformComponent* transformComponent = this->getNode<ShapeComponent>()->getNode<TransformComponent>();
        switch(playerInputComponent->getRotationAction()) {
            case PlayerInputComponent::PlayerAction::NONE: {
                break;
            }
            case PlayerInputComponent::PlayerAction::ROTATE_LEFT: {
                transformComponent->orientation = (static_cast<int>(transformComponent->orientation - (deltaTime * 360)) % 360);
                break;
            }
            case PlayerInputComponent::PlayerAction::ROTATE_RIGHT: {
                transformComponent->orientation = (static_cast<int>(transformComponent->orientation + (deltaTime * 360)) % 360);
                break;
            }
            default: {
                break;
            }
        }
        
        switch(playerInputComponent->getMovementAction()) {
            case PlayerInputComponent::PlayerAction::THRUST: {
                double radians = transformComponent->orientation * M_PI / 180;
                Eigen::Vector2f velocity = transformComponent->velocity;
                velocity.x() += (std::cos(radians) * acceleration);
                velocity.y() += (std::sin(radians) * acceleration);
                velocity.x() = std::clamp(velocity.x(), -maxSpeed, maxSpeed);
                velocity.y() = std::clamp(velocity.y(), -maxSpeed, maxSpeed);
                transformComponent->velocity = velocity;
                break;
            }
            case PlayerInputComponent::PlayerAction::HYPERSPACE: {
                playerInputComponent->reset();
                transformComponent->velocity = {0, 0};
                                
                int width = 0;
                int height = 0;
                ManagerHelper::get<GameSettingsManager>()->getWindowSize(width, height);                
                std::uniform_int_distribution<unsigned int> widthDistribution(0, width);
                std::uniform_int_distribution<unsigned int> heightDistribution(0, height);
                std::mt19937 generator(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
                this->setPosition({widthDistribution(generator), heightDistribution(generator)});
                return;
            }
            default: {
                break;
            }
        }
        
        Eigen::Vector2f position = this->getPosition();
        position.x() += (transformComponent->velocity.x() * deltaTime);
        position.y() += (transformComponent->velocity.y() * deltaTime);
        this->setPosition(position);
    }
}

void PlayerEntity::setPosition(const Eigen::Vector2f& position) {
    Eigen::Vector2f normalizedPosition = position;
    
    int width = 0;
    int height = 0;
    ManagerHelper::get<GameSettingsManager>()->getWindowSize(width, height);
    
    if(normalizedPosition.x() < 0) {
        normalizedPosition.x() = width;
    }
    else if(normalizedPosition.x() > width) {
        normalizedPosition.x() = 0;
    }
    
    if(normalizedPosition.y() < 0) {
        normalizedPosition.y() = height;
    }
    else if(normalizedPosition.y() > height) {
        normalizedPosition.y() = 0;
    }
    
    Entity::setPosition(normalizedPosition);
}
