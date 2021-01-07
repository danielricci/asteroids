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

SDL_Rect Entity::getEntityBounds() const {
    TransformComponent* transformComponent = getComponent<TransformComponent>();
    return transformComponent == nullptr
    ? SDL_Rect()
    : SDL_Rect {
        static_cast<int>(transformComponent->position.x()),
        static_cast<int>(transformComponent->position.y()),
        0,
        0
    };
}
