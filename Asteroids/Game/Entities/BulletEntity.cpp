#include "Engine/Components/CircleComponent.hpp"
#include "Engine/Components/RenderComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Engine/Managers/GameManager.hpp"
#include "Game/Entities/BulletEntity.hpp"
#include <cmath>

BulletEntity::BulletEntity() {
    this->addNode(new CircleComponent(1));
    this->addNode(new RenderComponent());
}

void BulletEntity::render(SDL_Renderer& renderer) {
    this->getNode<CircleComponent>()->render(renderer);
}

void BulletEntity::update(float deltaTime) {
    // TODO: For better accuracy, the distance should be capped when exceeded
    if(timeTravelled * speed >= MAX_DISTANCE) {
        ManagerHelper::get<GameManager>()->removeNode(this);
        return;
    }

    timeTravelled += deltaTime;
    
    Eigen::Vector2f velocity = this->getNode<TransformComponent>()->velocity;
    double radians = TransformComponent::toRadians(this->getOrientation());
    velocity.x() = (speed * std::cos(radians));
    velocity.y() = (speed * std::sin(radians));
    
    Eigen::Vector2f position = this->getPosition();
    position.x() += (velocity.x() * deltaTime);
    position.y() += (velocity.y() * deltaTime);
    this->setPosition(position);
}
