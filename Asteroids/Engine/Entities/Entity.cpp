#include "Engine/Entities/Entity.hpp"

Entity::Entity() {
    TransformComponent* transformComponent = new TransformComponent();
    this->addComponent(transformComponent);
}

Entity::~Entity() {
    for(Component* component : components) {
        if(component != nullptr) {
            delete component;
            component = nullptr;
        }
    }
    components.clear();
}

void Entity::addComponent(Component* component) {
    if(component != nullptr) {
        components.push_back(component);
    }
}

void Entity::setPosition(float x, float y) {
    TransformComponent* transformComponent = this->getComponent<TransformComponent>();
    if(transformComponent != nullptr) {
        transformComponent->positionVector = Eigen::Vector2f(x, y);
    }
}

void Entity::update(const SDL_Event &event) {
    // TODO: Entity::update(const SDL_Event &event)
}
