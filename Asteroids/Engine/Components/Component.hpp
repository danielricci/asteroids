#pragma once

#include "Engine/Entities/Entity.hpp"

#include <list>

class Entity;

class Component {
public:
    virtual ~Component() {
        for(Component* component : components) {
            delete component;
            component = nullptr;
        }
        components.clear();
    }

    template<typename T> T* getComponent() {
        T* myComponent = nullptr;
        for(Component* component : components) {
            if((myComponent = dynamic_cast<T*>(component)) != nullptr) {
                break;
            }
        }
        return myComponent;
    }
    
    Component* addComponent(Component* component) {
        if(component != nullptr) {
            components.push_back(component);
        }
        return component;
    }
    
    inline Entity* getParentEntity() const { return this->parentEntity; }
    
    bool isEnabled = true;
protected:
    Component(Entity* entity) {
        this->parentEntity = entity;
    }
private:
    // NOTE: What happens if a component is added to another component
    // TODO: Is that parent properly calculated, need to verify this
    Entity* parentEntity = nullptr;
    std::list<Component*> components;
};
