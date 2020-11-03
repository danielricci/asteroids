#include "Engine/Components/CircleComponent.hpp"
#include "Engine/Components/RenderComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Engine/Managers/GameManager.hpp"
#include "Game/Entities/BulletEntity.hpp"
#include "Game/Entities/PlayerEntity.hpp"
#include <cmath>

BulletEntity::BulletEntity() {
    this->addNode(new CircleComponent(1));
    this->addNode(new RenderComponent());
}

void BulletEntity::render(SDL_Renderer& renderer) {
    this->getNode<CircleComponent>()->render(renderer);
}

void BulletEntity::update(float deltaTime) {
    double radians = TransformComponent::toRadians(this->getOrientation());
    
    TransformComponent* transformComponent = this->getNode<TransformComponent>();
    Eigen::Vector2f velocity = transformComponent->velocity;
    velocity.x() = (speed * std::cos(radians));
    velocity.y() = (speed * std::sin(radians));
    
    Eigen::Vector2f position = this->getPosition();
    position.x() += (velocity.x() * deltaTime);
    position.y() += (velocity.y() * deltaTime);
    this->setPosition(position);
}

