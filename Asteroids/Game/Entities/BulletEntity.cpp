#include "Engine/Components/CircleComponent.hpp"
#include "Engine/Components/PhysicsComponent.hpp"
#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Managers/GameManager.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Game/Entities/BulletEntity.hpp"
#include <cmath>

BulletEntity::BulletEntity() {
    this->addComponent(new CircleComponent(1));
    PhysicsComponent* collisionComponent = new PhysicsComponent();
    collisionComponent->eventOnCollide = [this]() {
        ManagerHelper::clean(this);
    };
    this->addComponent(collisionComponent);
}

void BulletEntity::render(SDL_Renderer& renderer) {
    getComponent<CircleComponent>()->render(renderer);
}

void BulletEntity::update(const SDL_Event& event) {
    
}

void BulletEntity::update(float deltaTime) {
    if(timeTravelled * SPEED >= MAX_DISTANCE) {
        ManagerHelper::clean(this);
        return;
    }

    timeTravelled += deltaTime;
    
    Eigen::Vector2f velocity = getComponent<TransformComponent>()->velocity;
    double radians = TransformComponent::toRadians(this->getOrientation());
    velocity.x() = (SPEED * std::cos(radians));
    velocity.y() = (SPEED * std::sin(radians));
    
    Eigen::Vector2f position = getPosition();
    position.x() += (velocity.x() * deltaTime);
    position.y() += (velocity.y() * deltaTime);
    this->setPosition(position);
}
