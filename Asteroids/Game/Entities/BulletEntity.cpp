#include "Engine/Components/CircleComponent.hpp"
#include "Engine/Components/PhysicsComponent.hpp"
#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Managers/GameManager.hpp"
#include "Engine/Managers/SoundManager.hpp"
#include "Game/Entities/BulletEntity.hpp"
#include "Game/ManagerHelper.hpp"
#include <cmath>

BulletEntity::BulletEntity(bool fromPlayer) : fromPlayer(fromPlayer) {
    this->addComponent(new CircleComponent(1));
    PhysicsComponent* collisionComponent = new PhysicsComponent();
    collisionComponent->eventOnCollide.attach([this](Entity* sender, EventArgs args) {
        ManagerHelper::destroy(this);
    });
    this->addComponent(collisionComponent);
    
    if(fromPlayer) {
        ManagerHelper::get<SoundManager>()->getSound("fire.wav")->play();
    }
}

Eigen::Vector2f BulletEntity::getDimensions() const {
    return Eigen::Vector2f(1, 1);
}

void BulletEntity::update(float deltaTime) {
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
