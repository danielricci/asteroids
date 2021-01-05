#include "Engine/Components/PhysicsComponent.hpp"
#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Managers/GameManager.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Game/Entities/SaucerEntity.hpp"
#include <Eigen/Dense>
#include <iostream>

SaucerEntity::SaucerEntity() {
    for(const auto& part : saucerParts) {
        addComponent(new ShapeComponent(part));
    }
    
    PhysicsComponent* physicsComponent = new PhysicsComponent();
    physicsComponent->eventOnCollide.attach([this](Entity* sender, EventArgs args) {
        ManagerHelper::clean(this);
    });
    addComponent(physicsComponent);
}

SDL_Rect SaucerEntity::getEntityBounds() const {
    SDL_Rect bounds = getComponent<ShapeComponent>()->getShapeBounds();
    Eigen::Vector2f position = getPosition();
    bounds.x += position.x();
    bounds.y += position.y();
    return bounds;
}

void SaucerEntity::update(float deltaTime) {
    Eigen::Vector2f velocity = getComponent<TransformComponent>()->velocity;
    double radians = TransformComponent::toRadians(getOrientation());
    velocity.x() = (speed * std::cos(radians));
    velocity.y() = (speed * std::sin(radians));

    Eigen::Vector2f position = getPosition();
    position.x() += (velocity.x() * deltaTime);
    position.y() += (velocity.y() * deltaTime);
    setPosition(position);
}

void SaucerEntity::update(const SDL_Event& event) {
}

void SaucerEntity::render(SDL_Renderer& renderer) {
    getComponent<PhysicsComponent>()->render(renderer);
    for(ShapeComponent* shapeComponent : getComponents<ShapeComponent>()) {
        shapeComponent->render(renderer);
    }    
}
