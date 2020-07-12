#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Entities/Entity.hpp"

Entity::Entity() {
    this->addComponent(new TransformComponent());
}

Entity::~Entity() {
    for(Component* component : components) {
        if(component != nullptr) {
            delete component;
        }
    }
}

void Entity::addComponent(Component* component) {
    if(component != nullptr) {
        components.push_back(component);
    }
}

void Entity::update(const SDL_Event &event) {
    // TODO: Entity::update(const SDL_Event &event)
}
