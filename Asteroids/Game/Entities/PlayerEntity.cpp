#include "Engine/Components/PhysicsComponent.hpp"
#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Managers/WorldManager.hpp"
#include "Engine/Managers/WindowManager.hpp"
#include "Game/Components/PlayerInputComponent.hpp"
#include "Game/Entities/BulletEntity.hpp"
#include "Game/Entities/PlayerEntity.hpp"
#include "Game/Managers/ManagerHelper.hpp"
#include "Game/Particles/PlayerExplosionParticle.hpp"
#include <cmath>
#include <random>
#include <vector>

PlayerEntity::PlayerEntity() {
    setOrientation(TransformComponent::ROTATION_TOP);
    
    // TODO: Not true center but close enough for now
    SDL_Rect windowSize = ManagerHelper::get<WindowManager>()->getWindowSize();
    setPosition(Eigen::Vector2f(windowSize.w / 2, windowSize.h / 2));
    
    PlayerInputComponent* playerInputComponent = new PlayerInputComponent();
    playerInputComponent->eventOnShoot = std::bind(&PlayerEntity::onEventShoot, this);
    playerInputComponent->eventOnHyperspace = std::bind(&PlayerEntity::onEventHyperspace, this);
    playerInputComponent->eventOnThrust = std::bind(&PlayerEntity::onEventThrust, this, std::placeholders::_1);
    addComponent(playerInputComponent);
    
    ShapeComponent* playerShip = new ShapeComponent({{12, 0}, {-12, 10}, {-8, 5}, {-8, -5}, {-12, -10}, {12, 0}});
    //playerShip->setColor({255, 255, 0});
    //playerShip->setColor({0, 255, 0});
    playerShip->setName(PLAYER_SHIP);
    addComponent(playerShip);
        
    ShapeComponent* playerThrust = new ShapeComponent({{-11, -3}, {-20, 0}, {-10, 3}});
    playerThrust->setVisible(false);
    playerThrust->setName(PLAYER_SHIP_EXHAUST);
    addComponent(playerThrust);
    
    PhysicsComponent* physicsComponent = new PhysicsComponent();
    physicsComponent->eventOnCollide.attach(std::bind(&PlayerEntity::onEventCollide, this, std::placeholders::_1, std::placeholders::_2));
    addComponent(physicsComponent);
}

Eigen::AlignedBox2f PlayerEntity::getBounds() const {
    ShapeComponent* shapeComponent = this->getComponent<ShapeComponent>(PLAYER_SHIP);
    SDL_FRect rectangle = shapeComponent->getRectangle();
    
    Eigen::AlignedBox2f alignedBox;
    alignedBox.min() = this->getPosition() + Eigen::Vector2f(rectangle.x, rectangle.y);
    alignedBox.max() = Eigen::Vector2f(alignedBox.min().x() + rectangle.w, alignedBox.min().y() + rectangle.h);
    return alignedBox;
}

void PlayerEntity::onEventCollide(Entity* sender, EventArgs args) {
    BulletEntity* bulletEntity = dynamic_cast<BulletEntity*>(sender);
    if(bulletEntity != nullptr && bulletEntity->fromPlayer) {
        return;
    }
    
    ManagerHelper::setFeedbackState(this, false);
    
    PlayerExplosionParticle* playerExplosionParticle = new PlayerExplosionParticle();
    playerExplosionParticle->eventOnStop.attach([this](Entity* sender, EventArgs args) {
        ManagerHelper::destroy(this);
        ManagerHelper::broadcast(ManagerHelper::BroadcastEvent::EVENT_SPAWN_PLAYER, this, EventArgs::Empty());
    });
    playerExplosionParticle->play();
    playerExplosionParticle->setOrientation(this->getOrientation());
    playerExplosionParticle->setPosition(this->getPosition());
    ManagerHelper::get<WorldManager>()->addEntity(playerExplosionParticle);
    
    
    ManagerHelper::broadcast(ManagerHelper::BroadcastEvent::EVENT_PLAYER_HIT, this, EventArgs::Empty());
}

void PlayerEntity::onEventHyperspace() {
    velocity = Eigen::Vector2f::Zero();
    
    SDL_Rect windowSize = ManagerHelper::get<WindowManager>()->getWindowSize();

    std::uniform_int_distribution<unsigned int> widthDistribution(0, windowSize.w);
    std::uniform_int_distribution<unsigned int> heightDistribution(0, windowSize.h);
    std::mt19937 generator(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
    setPosition({widthDistribution(generator), heightDistribution(generator)});
}

void PlayerEntity::onEventThrust(bool isThrustActivated) {
    getComponent<ShapeComponent>(PLAYER_SHIP_EXHAUST)->setVisible(isThrustActivated);
}

void PlayerEntity::onEventShoot() {
    BulletEntity* bulletEntity = new BulletEntity(true);
    bulletEntity->setOrientation(getOrientation());

    ShapeComponent* playerShapeComponent = getComponent<ShapeComponent>(PLAYER_SHIP);
    Eigen::Vector2f finalFinalPosition = getWorldPosition((*playerShapeComponent)[0]);
    bulletEntity->setPosition({finalFinalPosition.x(), finalFinalPosition.y()});
    
    ManagerHelper::get<WorldManager>()->addEntity(bulletEntity);
}

void PlayerEntity::update(const SDL_Event& event) {
    GameEntity::update(event);
    switch(event.type) {
        case SDL_CONTROLLERAXISMOTION:
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
    GameEntity::update(deltaTime);
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
            velocity.x() += (std::cos(radians) * ACCELERATION);
            velocity.y() += (std::sin(radians) * ACCELERATION);
            velocity.x() = std::clamp(velocity.x(), -MAX_SPEED, MAX_SPEED);
            velocity.y() = std::clamp(velocity.y(), -MAX_SPEED, MAX_SPEED);
        }
        
        Eigen::Vector2f position = this->getPosition();
        position.x() += (velocity.x() * deltaTime);
        position.y() += (velocity.y() * deltaTime);
        setPosition(position);
    }
}
