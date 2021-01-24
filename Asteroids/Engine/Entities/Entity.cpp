#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Entities/Entity.hpp"
#include "Engine/Managers/WindowManager.hpp"

Entity::Entity() {
    addComponent(new TransformComponent());
}

Entity::~Entity() {
    for(Component* component : this->components) {
        if(component != nullptr) {
            delete component;
        }
    }
    this->components.clear();
}

void Entity::addComponent(Component* component) {
    if(component != nullptr) {
        this->components.push_back(component);
        component->setOwnerEntity(this);
    }
}

float Entity::getOrientation() const {
    TransformComponent* transformComponent = getComponent<TransformComponent>();
    return transformComponent == nullptr ? 0.f : transformComponent->orientation;
}

Eigen::Vector2f Entity::getPosition() const {
    TransformComponent* transformComponent = getComponent<TransformComponent>();
    return transformComponent == nullptr ? Eigen::Vector2f(0, 0) : transformComponent->position;
}

Eigen::Vector2f Entity::getPosition(const Eigen::Vector2f& vertex) const {
    float rotation = TransformComponent::toRadians(getOrientation());

    float cosResult = std::cos(rotation);
    float sinResult = std::sin(rotation);
    float expr1 = (cosResult * vertex.x()) - (sinResult * vertex.y());
    float expr2 = (sinResult * vertex.x()) + (cosResult * vertex.y());
    
    Eigen::Vector2f worldPosition = getPosition();
    worldPosition.x() += expr1;
    worldPosition.y() += expr2;

    return worldPosition;
}

void Entity::setPosition(const Eigen::Vector2f& position) {
    getComponent<TransformComponent>()->position = position;
}


void Entity::setOrientation(int orientation) {
    getComponent<TransformComponent>()->orientation = orientation;
}
