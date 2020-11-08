#include "Engine/Components/CircleComponent.hpp"
#include "Engine/Components/RenderComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Engine/Managers/GameManager.hpp"
#include "Game/Entities/BulletEntity.hpp"
#include "Game/Entities/PlayerEntity.hpp"
#include <cmath>
#include <iostream>

BulletEntity::BulletEntity() {
    this->addNode(new CircleComponent(1));
    this->addNode(new RenderComponent());
}

void BulletEntity::render(SDL_Renderer& renderer) {
    this->getNode<CircleComponent>()->render(renderer);
}

void BulletEntity::update(float deltaTime) {
    
    //timeTravelled += 
    
    
    if(distanceSqr >= MAX_DISTANCE_SQR) {
        //return;
    }
    
    Eigen::Vector2f velocity = this->getNode<TransformComponent>()->velocity;
    double radians = TransformComponent::toRadians(this->getOrientation());
    velocity.x() = (speed * std::cos(radians));
    velocity.y() = (speed * std::sin(radians));
    
    Eigen::Vector2f oldPosition = this->getPosition();
    Eigen::Vector2f newPosition = {
        oldPosition.x() + (velocity.x() * deltaTime),
        oldPosition.y() + (velocity.y() * deltaTime)
    };
    
    distanceSqr += (std::pow(newPosition.x() - oldPosition.x(), 2) + std::pow(newPosition.y() - oldPosition.y(), 2));
    std::cout << x << std::endl;
    this->setPosition(newPosition);
}
