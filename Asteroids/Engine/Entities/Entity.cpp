#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Entities/Entity.hpp"

Entity::Entity() {
    this->addNode(new TransformComponent());
}

void Entity::update(float deltaTime) {
}

void Entity::update(const SDL_Event& event) {
}

void Entity::render(SDL_Renderer& renderer) {
}
