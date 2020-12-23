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

float Entity::getOrientation() const {
    TransformComponent* transformComponent = getComponent<TransformComponent>();
    return transformComponent == nullptr ? 0.f : transformComponent->orientation;
}

void Entity::setOrientation(int orientation) {
    getComponent<TransformComponent>()->orientation = orientation;
}

Eigen::Vector2f Entity::getOrigin() const {
    TransformComponent* transformComponent = getComponent<TransformComponent>();
    return transformComponent == nullptr ? Eigen::Vector2f(0, 0) : transformComponent->origin;
}

void Entity::setOrigin(const Eigen::Vector2f& origin) {
    getComponent<TransformComponent>()->origin = origin;
}

Eigen::Vector2f Entity::getDimension() const {
    TransformComponent* transformComponent = getComponent<TransformComponent>();
    return transformComponent == nullptr ? Eigen::Vector2f(0, 0) : transformComponent->dimension;
}

SDL_Rect Entity::getEntityBounds() const {
    TransformComponent* transformComponent = getComponent<TransformComponent>();
    return transformComponent == nullptr
    ? SDL_Rect()
    : SDL_Rect {
        static_cast<int>(transformComponent->position.x()),
        static_cast<int>(transformComponent->position.y()),
        static_cast<int>(transformComponent->dimension.x()),
        static_cast<int>(transformComponent->dimension.y())
    };
}

void Entity::setDimension(const Eigen::Vector2f& dimension) const {
    getComponent<TransformComponent>()->dimension = dimension;
}
