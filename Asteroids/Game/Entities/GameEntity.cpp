#include "Engine/Managers/ManagerHelper.hpp"
#include "Engine/Managers/WindowManager.hpp"
#include "Engine/Components/PhysicsComponent.hpp"
#include "Game/Entities/GameEntity.hpp"

void GameEntity::setPosition(const Eigen::Vector2f& position) {
    SDL_Rect windowSize = ManagerHelper::get<WindowManager>()->getWindowSize();
    
    Eigen::Vector2f normalizedPosition = position;
    if(normalizedPosition.x() < 0) {
        normalizedPosition.x() += windowSize.w;
    }
    else if(normalizedPosition.x() > windowSize.w) {
        normalizedPosition.x() -= windowSize.w;
    }
    
    if(normalizedPosition.y() < 0) {
        normalizedPosition.y() += windowSize.h;
    }
    else if(normalizedPosition.y() > windowSize.h) {
        normalizedPosition.y() -= windowSize.h;
    }
    Entity::setPosition(normalizedPosition);
}

void GameEntity::collision(Entity& entity) {
    PhysicsComponent* physicsComponent = this->getComponent<PhysicsComponent>();
    if(physicsComponent != nullptr && entity.hasComponent<PhysicsComponent>()) {
        if(physicsComponent->collide(entity) && physicsComponent->eventOnCollide != nullptr) {
            physicsComponent->eventOnCollide();
        }
    }
}
