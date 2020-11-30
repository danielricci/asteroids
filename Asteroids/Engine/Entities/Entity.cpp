#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Entities/Entity.hpp"
#include "Engine/Managers/WindowManager.hpp"
#include "Engine/Managers/ManagerHelper.hpp"

Entity::Entity() {
    addComponent(new TransformComponent());
}

void Entity::addComponent(Component* component) {
    if(component != nullptr) {
        this->components.push_back(component);
        component->setOwnerEntity(this);
    }
}

template<class T> T* Entity::getComponent<T>(std::string name) {
    T* resultComponent = nullptr;
    for(Component* component : components) {
        T* componentCast = dynamic_cast<T*>(component);
        if(componentCast != nullptr) {
            if(name.empty() || name == component->name) {
                resultComponent = componentCast;
                break;
            }
        }
    }
    return resultComponent;
}

void Entity::setPosition(const Eigen::Vector2f& position) {
    SDL_Rect windowSize = ManagerHelper::get<WindowManager>()->getWindowSize();
    
    Eigen::Vector2f normalizedPosition = position;
    if(normalizedPosition.x() < 0) {
        normalizedPosition.x() += windowSize.w;
    }
    else if(normalizedPosition.x() > windowSize.w) {
        normalizedPosition.x() -= windowSize.w;
    }
    
    if(normalizedPosition.y() < 0) {
        normalizedPosition.y() += windowSize.h;
    }
    else if(normalizedPosition.y() > windowSize.h) {
        normalizedPosition.y() -= windowSize.h;
    }
    
    this->getComponent<TransformComponent>()->position = normalizedPosition;
}
