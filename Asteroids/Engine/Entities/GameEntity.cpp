#include "Engine/Components/PhysicsComponent.hpp"
#include "Engine/Entities/GameEntity.hpp"
#include "Engine/Managers/WindowManager.hpp"
#include "Engine/Managers/ManagerHelper.hpp"

void GameEntity::collisionCheck(Entity& entity) {
    PhysicsComponent* physicsComponent = getComponent<PhysicsComponent>();
    if(physicsComponent != nullptr && entity.hasComponent<PhysicsComponent>() && physicsComponent->isCollidedWith(entity)) {
        physicsComponent->eventOnCollide.invoke(&entity);
        entity.getComponent<PhysicsComponent>()->eventOnCollide.invoke(this);
    }
}

Eigen::AlignedBox2f GameEntity::getBounds() const {
    Eigen::AlignedBox2f bounds;
    bounds.min() = this->getPosition();
    bounds.max() = bounds.min() + this->getDimensions();
    return bounds;
}

void GameEntity::render(SDL_Renderer& renderer) {
    for(Component* component : this->getComponents()) {
        component->render(renderer);
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
