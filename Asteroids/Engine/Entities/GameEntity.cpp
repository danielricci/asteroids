#include "Engine/Components/PhysicsComponent.hpp"
#include "Engine/Managers/WindowManager.hpp"
#include "Engine/Entities/GameEntity.hpp"
#include "Engine/Managers/ManagerHelper.hpp"

void GameEntity::collisionCheck(Entity& entity) {
    PhysicsComponent* physicsComponent = getComponent<PhysicsComponent>();
    if(physicsComponent != nullptr && entity.hasComponent<PhysicsComponent>() && physicsComponent->isCollidedWith(entity)) {
        physicsComponent->eventOnCollide.invoke(&entity);
        entity.getComponent<PhysicsComponent>()->eventOnCollide.invoke(this);
    }
}

Eigen::AlignedBox2f GameEntity::getBounds() const {
    return Eigen::AlignedBox2f();
}

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
