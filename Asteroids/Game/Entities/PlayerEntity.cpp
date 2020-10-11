#include "Engine/Components/RenderComponent.hpp"
#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/SoundComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Engine/Managers/GameSettingsManager.hpp"
#include "Game/Components/PlayerInputComponent.hpp"
#include "Game/Entities/PlayerEntity.hpp"
#include <cmath>
#include <random>

PlayerEntity::PlayerEntity() {
    TransformComponent* playerTransform = this->getNode<TransformComponent>();
    playerTransform->orientation = TransformComponent::ORIENTATION_NORTH;
    
    ShapeComponent* playerShapeComponent = new ShapeComponent({{0, 0}, {-24, 10}, {-20, 0}, {-24, -10}, {0, 0}});
    playerShapeComponent->name = PLAYER_SHAPE;
    
    ShapeComponent* playerThrust = new ShapeComponent({{-9, -3}, {-20, 0}, {-9, 3}});
    playerThrust->name = PLAYER_THRUST_SHAPE;
    
    // Translate the player ships' shape positions to the right on the axis so that the
    // the world position of the entity has its origin at the center (avoids having to do any origin normaliation for each rotational tick)
    SDL_Point shapeCenterPoint = playerShapeComponent->getShapeCenter();
    for(int i = 0; i < playerShapeComponent->getSize(); ++i) {
        (*playerShapeComponent)[i].x += shapeCenterPoint.x;
    }
    
    SoundComponent* thrustSoundComponent = new SoundComponent("Thrust.wav");
    thrustSoundComponent->name = THRUST_SOUND;
    
    this->addNode(thrustSoundComponent);
    this->addNode(playerThrust);
    this->addNode(playerShapeComponent);
    this->addNode(new PlayerInputComponent());
}

void PlayerEntity::render(SDL_Renderer& renderer) {
    PlayerInputComponent* playerInputComponent = this->getNode<PlayerInputComponent>();
    RenderComponent* thrustRenderComponent = this->getNode<ShapeComponent>(this->PLAYER_THRUST_SHAPE)->getNode<RenderComponent>();
    thrustRenderComponent->isVisible = playerInputComponent->getMovementAction() == PlayerInputComponent::PlayerAction::THRUST;
    for(ShapeComponent* shapeComponent : this->getNodes<ShapeComponent>()) {
        shapeComponent->render(renderer);
    }
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
        // Compute the orientation
        TransformComponent* playerTransform = this->getNode<TransformComponent>();
        switch(playerInputComponent->getRotationAction()) {
            case PlayerInputComponent::PlayerAction::ROTATE_LEFT: {
                playerTransform->orientation = (static_cast<int>(playerTransform->orientation - (deltaTime * 360)) % 360);
                break;
            }
            case PlayerInputComponent::PlayerAction::ROTATE_RIGHT: {
                playerTransform->orientation = (static_cast<int>(playerTransform->orientation + (deltaTime * 360)) % 360);
                break;
            }
            default: {
                break;
            }
        }
        // Compute the position
        switch(playerInputComponent->getMovementAction()) {
            case PlayerInputComponent::PlayerAction::THRUST: {
                double radians = TransformComponent::toRadians(playerTransform->orientation);
                Eigen::Vector2f velocity = playerTransform->velocity;
                velocity.x() += (std::cos(radians) * acceleration);
                velocity.y() += (std::sin(radians) * acceleration);
                velocity.x() = std::clamp(velocity.x(), -maxSpeed, maxSpeed);
                velocity.y() = std::clamp(velocity.y(), -maxSpeed, maxSpeed);
                playerTransform->velocity = velocity;
                
                // TODO
                //this->getNode<SoundComponent>(THRUST_SOUND)->play(SoundComponent::INFINITE_LOOP);
                break;
            }
            case PlayerInputComponent::PlayerAction::HYPERSPACE: {
                // Stop the player from moving
                playerInputComponent->reset();
                playerTransform->velocity = {0, 0};
                // Compute the new location
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
                // TODO
                //this->getNode<SoundComponent>(THRUST_SOUND)->stop();
                break;
            }
        }
        // Set the position
        Eigen::Vector2f position = this->getPosition();
        position.x() += (playerTransform->velocity.x() * deltaTime);
        position.y() += (playerTransform->velocity.y() * deltaTime);
        this->setPosition(position);
    }
}

void PlayerEntity::setPosition(const Eigen::Vector2f& position) {
    int width = 0;
    int height = 0;
    ManagerHelper::get<GameSettingsManager>()->getWindowSize(width, height);
    
    Eigen::Vector2f normalizedPosition = position;
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
