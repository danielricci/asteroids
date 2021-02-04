#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Entities/Entity.hpp"

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

Eigen::Vector2f Entity::getDimensions() const {
    TransformComponent* transformComponent = getComponent<TransformComponent>();
    return transformComponent == nullptr ? Eigen::Vector2f::Zero() : transformComponent->dimensions;
}

float Entity::getOrientation() const {
    TransformComponent* transformComponent = getComponent<TransformComponent>();
    return transformComponent == nullptr ? 0.f : transformComponent->orientation;
}

Eigen::Vector2f Entity::getPosition() const {
    TransformComponent* transformComponent = getComponent<TransformComponent>();
    return transformComponent == nullptr ? Eigen::Vector2f::Zero() : transformComponent->position;
}

Eigen::Vector2f Entity::getPosition(const Eigen::Vector2f& vertex, bool includeWorldPosition) const {
    float rotation = TransformComponent::toRadians(getOrientation());
    float cosResult = std::cos(rotation);
    float sinResult = std::sin(rotation);
    float positionX = (cosResult * vertex.x()) - (sinResult * vertex.y());
    float positionY = (sinResult * vertex.x()) + (cosResult * vertex.y());
    
    Eigen::Vector2f position(positionX, positionY);
    if(includeWorldPosition) {
        position += getPosition();
    }
    
    return position;
}

void Entity::setDimensions(const Eigen::Vector2f& dimensions) {
    getComponent<TransformComponent>()->dimensions = dimensions;
}

void Entity::setPosition(const Eigen::Vector2f& position) {
    getComponent<TransformComponent>()->position = position;
}

void Entity::setOrientation(int orientation) {
    getComponent<TransformComponent>()->orientation = orientation;
}
