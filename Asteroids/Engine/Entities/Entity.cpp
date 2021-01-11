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

Eigen::Vector2f Entity::getPosition() const {
    TransformComponent* transformComponent = getComponent<TransformComponent>();
    return transformComponent == nullptr ? Eigen::Vector2f(0, 0) : transformComponent->position;
}

void Entity::setPosition(const Eigen::Vector2f& position) {
    getComponent<TransformComponent>()->position = position;
}

float Entity::getRotation() const {
    TransformComponent* transformComponent = getComponent<TransformComponent>();
    return transformComponent == nullptr ? 0.f : transformComponent->rotation;
}

void Entity::setRotation(int orientation) {
    getComponent<TransformComponent>()->rotation = orientation;
}
