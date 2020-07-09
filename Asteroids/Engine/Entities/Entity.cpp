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

Component* Entity::addComponent(Component* component) {
    components.push_back(component);
    return component;
}

void Entity::update(const SDL_Event &event) {
}
