#include "Engine/Entities/Entity.hpp"

Entity::Entity() {
    this->addNode(new TransformComponent());
}

Eigen::Vector2f Entity::getPosition() const {
    TransformComponent* transformComponent = this->getNode<TransformComponent>();
    return transformComponent == nullptr ? Eigen::Vector2f(0, 0) : transformComponent->positionVector;
}

void Entity::update(const SDL_Event& event) {
    // TODO: Entity::update(const SDL_Event &event)
}

void Entity::render(SDL_Renderer& renderer) {
    // TODO: Entity::render(SDL_Renderer& renderer)
}
