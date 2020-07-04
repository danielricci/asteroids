#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Entities/Entity.hpp"

Entity::Entity(int x, int y, int width, int height) {
    this->addComponent(new TransformComponent(this, x, y, width, height));
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

void Entity::processEvent(const SDL_Event &event) {
}
