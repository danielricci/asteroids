#include "Engine/Components/Component.hpp"
#include "Engine/Components/TransformComponent.hpp"

Component::~Component() {
    for(Component* component : components) {
        delete component;
        component = nullptr;
    }
    components.clear();
}

void Component::setPosition(const Eigen::Vector2f& position) {
    TransformComponent* transform = this->getComponent<TransformComponent>();
    if(transform != nullptr) {
        transform->positionVector = position;
    }
}

void Component::addComponent(Component* component) {
    if(component != nullptr) {
        component->setParentNode(this);
        components.push_back(component);
    }
}
