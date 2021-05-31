#include "Engine/Components/CircleComponent.hpp"
#include "Engine/Components/PhysicsComponent.hpp"
#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Managers/WorldManager.hpp"
#include "Engine/Managers/SoundManager.hpp"
#include "Game/Entities/BulletEntity.hpp"
#include "Game/Entities/PlayerEntity.hpp"
#include "Game/Managers/ManagerHelper.hpp"
#include <cmath>

BulletEntity::BulletEntity(GameEntity* owner) : fromPlayer(dynamic_cast<PlayerEntity*>(owner) != nullptr), ownerId(owner->entityId) {
    this->addComponent(new CircleComponent(1));
    
    PhysicsComponent* collisionComponent = new PhysicsComponent();
    collisionComponent->eventOnCollide.attach([this](Entity* sender, EventArgs args) {
        if(sender->entityId != this->ownerId) {
            ManagerHelper::destroy(this);
        }
    });
    this->addComponent(collisionComponent);
}

Eigen::Vector2f BulletEntity::getDimensions() const {
    return Eigen::Vector2f(1, 1);
}

void BulletEntity::update(float deltaTime) {
    if(timeTravelled == 0) {
        ManagerHelper::get<SoundManager>()->getSound("fire")->play();
    }
    
    if(timeTravelled * SPEED >= MAX_DISTANCE) {
        ManagerHelper::destroy(this);
        return;
    }

    timeTravelled += deltaTime;
    
    double radians = TransformComponent::toRadians(this->getOrientation());
    velocity.x() = (SPEED * std::cos(radians));
    velocity.y() = (SPEED * std::sin(radians));
    
    Eigen::Vector2f position = getPosition();
    position.x() += (velocity.x() * deltaTime);
    position.y() += (velocity.y() * deltaTime);
    this->setPosition(position);
}
