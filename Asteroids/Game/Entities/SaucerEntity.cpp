#include "Engine/Components/PhysicsComponent.hpp"
#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Engine/Managers/GameManager.hpp"
#include "Game/Entities/SaucerEntity.hpp"
#include <Eigen/Dense>

SaucerEntity::SaucerEntity() {
    addComponent(new ShapeComponent({{5, -5}, {10, -15}, {25, -15}, {30, -5}}));
    addComponent(new ShapeComponent({{0, 0}, {5, -5}, {30, -5}, {36, 1}}));
    addComponent(new ShapeComponent({{0, 0}, {5, 5}, {30, 5}, {35, 0}}));
    
    PhysicsComponent* physicsComponent = new PhysicsComponent();
    physicsComponent->eventOnCollide.attach([this](Entity* sender, EventArgs args) {
        ManagerHelper::clean(this);
    });
    addComponent(physicsComponent);
}

void SaucerEntity::update(float deltaTime) {
    double radians = TransformComponent::toRadians(getOrientation());
    velocity.x() = (speed * std::cos(radians));
    velocity.y() = (speed * std::sin(radians));

    Eigen::Vector2f position = getPosition();
    position.x() += (velocity.x() * deltaTime);
    position.y() += (velocity.y() * deltaTime);
    setPosition(position);
}

void SaucerEntity::render(SDL_Renderer& renderer) {
    for(ShapeComponent* shapeComponent : getComponents<ShapeComponent>()) {
        shapeComponent->render(renderer);
    }    
}
