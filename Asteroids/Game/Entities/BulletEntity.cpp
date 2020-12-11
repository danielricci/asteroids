#include "Engine/Components/CircleComponent.hpp"
#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Managers/GameManager.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Game/Entities/BulletEntity.hpp"
#include <cmath>

BulletEntity::BulletEntity() {
    this->addComponent(new CircleComponent(1));
}

void BulletEntity::render(SDL_Renderer& renderer) {
    this->getComponent<CircleComponent>()->render(renderer);
}

void BulletEntity::update(const SDL_Event& event) {
    
}

void BulletEntity::update(float deltaTime) {
//    if(timeTravelled * speed >= MAX_DISTANCE) {
//        ManagerHelper::get<GameManager>()->removeNode(this);
//        return;
//    }

    timeTravelled += deltaTime;
    
    Eigen::Vector2f velocity = getComponent<TransformComponent>()->velocity;
    double radians = TransformComponent::toRadians(this->getOrientation());
    velocity.x() = (speed * std::cos(radians));
    velocity.y() = (speed * std::sin(radians));
    
    Eigen::Vector2f position = getPosition();
    position.x() += (velocity.x() * deltaTime);
    position.y() += (velocity.y() * deltaTime);
    this->setPosition(position);
}
