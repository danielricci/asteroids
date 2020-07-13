#include "Engine/Entities/Entity.hpp"

Entity::Entity() {
    this->addNode(new TransformComponent());
}

Eigen::Vector2f Entity::getPosition() const {
    TransformComponent* transformComponent = this->getNode<TransformComponent>();
    return transformComponent == nullptr ? Eigen::Vector2f(0, 0) : transformComponent->positionVector;
}

void Entity::setPosition(float x, float y) {
    TransformComponent* transformComponent = this->getNode<TransformComponent>();
    if(transformComponent != nullptr) {
        transformComponent->positionVector = Eigen::Vector2f(x, y);
    }
}

void Entity::update(const SDL_Event &event) {
    // TODO: Entity::update(const SDL_Event &event)
}

