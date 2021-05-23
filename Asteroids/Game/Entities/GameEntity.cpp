#include "Engine/Components/PhysicsComponent.hpp"
#include "Engine/Managers/WindowManager.hpp"
#include "Game/Entities/GameEntity.hpp"
#include "Game/Managers/ManagerHelper.hpp"

void GameEntity::collisionCheck(Entity& entity) {
    PhysicsComponent* physicsComponent = getComponent<PhysicsComponent>();
    if(physicsComponent != nullptr && entity.hasComponent<PhysicsComponent>() && physicsComponent->isCollidedWith(entity)) {
        physicsComponent->eventOnCollide.invoke(&entity);
        entity.getComponent<PhysicsComponent>()->eventOnCollide.invoke(this);
    }
}

Eigen::AlignedBox2f GameEntity::getBounds() const {
    Eigen::AlignedBox2f bounds;
    bounds.min() = getPosition();
    bounds.max() = bounds.min() + getDimensions();
    return bounds;
}

void GameEntity::render(SDL_Renderer& renderer) {
    for(Component* component : getComponents()) {
        if(component->getVisible()) {
            component->render(renderer);
        }
    }
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

void GameEntity::update(float deltaTime) {
}

void GameEntity::update(const SDL_Event& event) {
}
