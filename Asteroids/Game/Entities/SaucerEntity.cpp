#include "Engine/Components/PhysicsComponent.hpp"
#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Engine/Managers/GameManager.hpp"
#include "Game/Entities/SaucerEntity.hpp"
#include <Eigen/Dense>

SaucerEntity::SaucerEntity() {
    addComponent(new ShapeComponent({
        // Top shape
        {5, -5},
        {10, -15},
        {25, -15},
        {30, -5},
        {5, -5},
        // Bottom shape
        {0, 0},
        {5, 5},
        {30, 5},
        {35, 0},
        {30, -5}
    }));
    
    PhysicsComponent* physicsComponent = new PhysicsComponent();
    physicsComponent->eventOnCollide.attach([this](Entity* sender, EventArgs args) {
        ManagerHelper::clean(this);
    });
    addComponent(physicsComponent);
}

Eigen::AlignedBox2f SaucerEntity::getBounds() const {
    ShapeComponent* shapeComponent = this->getComponent<ShapeComponent>();
    SDL_FRect rectangle = shapeComponent->getRectangle();
    
    Eigen::AlignedBox2f alignedBox;
    alignedBox.min() = this->getPosition() + Eigen::Vector2f(rectangle.x, rectangle.y);
    alignedBox.max() = Eigen::Vector2f(alignedBox.min().x() + rectangle.w, alignedBox.min().y() + rectangle.h);
    return alignedBox;
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
