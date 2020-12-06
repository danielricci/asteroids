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

template<typename T> T* Entity::getComponent(const std::string& name) const {
    T* result = nullptr;
    for(Component* component : components) {
        T* cast = dynamic_cast<T*>(component);
        if(cast != nullptr) {
            if(name.empty() || name == cast->name) {
                result = cast;
                break;
            }
        }
    }
    return result;
}

template<typename T> std::list<T*> Entity::getComponents() const {
    std::list<T*> components;
    for(Component* component : this->components) {
        T* cast = dynamic_cast<T*>(component);
        if(cast != nullptr) {
            components.push_back(cast);
        }
    }
    return components;
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

void Entity::setDimension(const Eigen::Vector2f& dimension) const {
    getComponent<TransformComponent>()->dimension = dimension;
}
