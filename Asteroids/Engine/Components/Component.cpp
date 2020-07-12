#include "Engine/Components/Component.hpp"
#include "Engine/Components/TransformComponent.hpp"

Component::~Component() {
    for(Component* component : components) {
        delete component;
        component = nullptr;
    }
    components.clear();
}

void Component::addComponent(Component* component) {
    components.push_back(component);
}
