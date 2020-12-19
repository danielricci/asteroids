#include "Engine/Components/CollisionComponent.hpp"
#include "Engine/Components/RenderComponent.hpp"
#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Managers/GameManager.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Engine/Managers/WindowManager.hpp"
#include "Game/Components/PlayerInputComponent.hpp"
#include "Game/Entities/BulletEntity.hpp"
#include "Game/Entities/PlayerEntity.hpp"
#include <cmath>
#include <random>
#include <iostream>

PlayerEntity::PlayerEntity() {
    getComponent<TransformComponent>()->orientation = TransformComponent::ORIENTATION_NORTH;

    // Player input bindings
    PlayerInputComponent* playerInputComponent = new PlayerInputComponent();
    playerInputComponent->eventOnShoot = std::bind(&PlayerEntity::onEventShoot, this);
    playerInputComponent->eventOnHyperspace = std::bind(&PlayerEntity::onEventHyperspace, this);
    playerInputComponent->eventOnThrust = [this](bool value) {
        this->getComponent<ShapeComponent>(PLAYER_THRUST_SHAPE)->setIsVisible(value);
    };
    addComponent(playerInputComponent);

    // Create the player ship
    ShapeComponent* playerShapeComponent = new ShapeComponent({{0, 0}, {-24, 10}, {-20, 0}, {-24, -10}, {0, 0}});
    playerShapeComponent->name = PLAYER_SHAPE;
    addComponent(playerShapeComponent);
    
    // Translate the player ships' shape positions so that the
    // world position of the entity has its origin at the center (avoids having to do any origin normalization for each rotational tick)
    SDL_Point shapeCenterPoint = playerShapeComponent->getShapeCenter();
    for(int i = 0; i < playerShapeComponent->getSize(); ++i) {
        (*playerShapeComponent)[i].x += shapeCenterPoint.x;
    }
    
    // Create the shape for when the player is moving
    ShapeComponent* playerThrust = new ShapeComponent({{-9, -3}, {-20, 0}, {-9, 3}});
    playerThrust->name = PLAYER_THRUST_SHAPE;
    this->addComponent(playerThrust);
}

void PlayerEntity::render(SDL_Renderer& renderer) {
    for(ShapeComponent* shapeComponent : this->getComponents<ShapeComponent>()) {
        if(shapeComponent->name == PLAYER_THRUST_SHAPE && !this->getComponent<PlayerInputComponent>()->getIsThrustActivated()) {
            continue;
        }

        shapeComponent->render(renderer);
    }
}

void PlayerEntity::update(const SDL_Event& event) {
    switch(event.type) {
        case SDL_KEYDOWN:
        case SDL_KEYUP: {
            PlayerInputComponent* playerInputComponent = this->getComponent<PlayerInputComponent>();
            if(playerInputComponent != nullptr) {
                playerInputComponent->update(event);
            }
            break;
        }
    }
}

void PlayerEntity::update(float deltaTime) {
    PlayerInputComponent* playerInputComponent = getComponent<PlayerInputComponent>();
    if(playerInputComponent != nullptr) {
        TransformComponent* playerTransform = getComponent<TransformComponent>();
        switch(playerInputComponent->getRotationAction()) {
            case PlayerInputComponent::RotationAction::ROTATE_LEFT: {
                playerTransform->orientation = (static_cast<int>(playerTransform->orientation - (deltaTime * 360)) % 360);
                break;
            }
            case PlayerInputComponent::RotationAction::ROTATE_RIGHT: {
                playerTransform->orientation = (static_cast<int>(playerTransform->orientation + (deltaTime * 360)) % 360);
                break;
            }
            default: {
                break;
            }
        }
        
        if(playerInputComponent->getIsThrustActivated()) {
            double radians = TransformComponent::toRadians(playerTransform->orientation);
            Eigen::Vector2f velocity = playerTransform->velocity;
            velocity.x() += (std::cos(radians) * acceleration);
            velocity.y() += (std::sin(radians) * acceleration);
            velocity.x() = std::clamp(velocity.x(), -maxSpeed, maxSpeed);
            velocity.y() = std::clamp(velocity.y(), -maxSpeed, maxSpeed);
            playerTransform->velocity = velocity;
        }
        
        Eigen::Vector2f position = this->getPosition();
        position.x() += (playerTransform->velocity.x() * deltaTime);
        position.y() += (playerTransform->velocity.y() * deltaTime);
        this->setPosition(position);
    }
}

void PlayerEntity::onEventHyperspace() {
    TransformComponent* transformComponent = getComponent<TransformComponent>();
    transformComponent->velocity = {0, 0};

    SDL_Rect windowSize = ManagerHelper::get<WindowManager>()->getWindowSize();

    std::uniform_int_distribution<unsigned int> widthDistribution(0, windowSize.w);
    std::uniform_int_distribution<unsigned int> heightDistribution(0, windowSize.h);
    std::mt19937 generator(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
    setPosition({widthDistribution(generator), heightDistribution(generator)});
}

void PlayerEntity::onEventShoot() {
    BulletEntity* bulletEntity = new BulletEntity();
    bulletEntity->setOrientation(getOrientation());

    ShapeComponent* playerShapeComponent = getComponent<ShapeComponent>(PLAYER_SHAPE);
    SDL_Point finalPosition = playerShapeComponent->getVertexPosition((*playerShapeComponent)[0]);
    bulletEntity->setPosition({finalPosition.x, finalPosition.y});
    
    ManagerHelper::get<GameManager>()->addEntity(bulletEntity);
}
