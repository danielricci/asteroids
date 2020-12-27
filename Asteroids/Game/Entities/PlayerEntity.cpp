#include "Engine/Components/PhysicsComponent.hpp"
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

PlayerEntity::PlayerEntity() {
    setOrientation(TransformComponent::ORIENTATION_NORTH);
        
    PlayerInputComponent* playerInputComponent = new PlayerInputComponent();
    playerInputComponent->eventOnShoot = std::bind(&PlayerEntity::onEventShoot, this);
    playerInputComponent->eventOnHyperspace = std::bind(&PlayerEntity::onEventHyperspace, this);
    playerInputComponent->eventOnThrust = [this](bool value) {
        getComponent<ShapeComponent>(PLAYER_SHIP_EXHAUST)->setIsVisible(value);
    };
    addComponent(playerInputComponent);
    
    ShapeComponent* playerShip = new ShapeComponent({{10, 0}, {-14, 10}, {-10, 0}, {-14, -10}, {10, 0}});
    playerShip->name = PLAYER_SHIP;
    addComponent(playerShip);
        
    ShapeComponent* playerThrust = new ShapeComponent({{-11, -3}, {-20, 0}, {-10, 3}});
    playerThrust->name = PLAYER_SHIP_EXHAUST;
    addComponent(playerThrust);
    
    PhysicsComponent* physicsComponent = new PhysicsComponent();
    physicsComponent->eventOnCollide = [this]() {
        onEventHyperspace();
    };
    addComponent(physicsComponent);
}

SDL_Rect PlayerEntity::getEntityBounds() const {
    return getComponent<ShapeComponent>(PLAYER_SHIP)->getShapeBounds();
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

    ShapeComponent* playerShapeComponent = getComponent<ShapeComponent>(PLAYER_SHIP);
    SDL_Point finalPosition = playerShapeComponent->getVertexPosition((*playerShapeComponent)[0]);
    bulletEntity->setPosition({finalPosition.x, finalPosition.y});
    
    ManagerHelper::get<GameManager>()->addEntity(bulletEntity);
}

void PlayerEntity::render(SDL_Renderer& renderer) {
    for(ShapeComponent* shapeComponent : this->getComponents<ShapeComponent>()) {
        if(shapeComponent->name == PLAYER_SHIP_EXHAUST && !this->getComponent<PlayerInputComponent>()->getIsThrustActivated()) {
            continue;
        }

        shapeComponent->render(renderer);
    }
    getComponent<PhysicsComponent>()->render(renderer);
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
            velocity.x() += (std::cos(radians) * ACCELERATION);
            velocity.y() += (std::sin(radians) * ACCELERATION);
            velocity.x() = std::clamp(velocity.x(), -MAX_SPEED, MAX_SPEED);
            velocity.y() = std::clamp(velocity.y(), -MAX_SPEED, MAX_SPEED);
            playerTransform->velocity = velocity;
        }
        
        Eigen::Vector2f position = this->getPosition();
        position.x() += (playerTransform->velocity.x() * deltaTime);
        position.y() += (playerTransform->velocity.y() * deltaTime);
        setPosition(position);
    }
}
