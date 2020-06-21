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
    
    inline Entity* getEntity() const { return this->entity; }
    
    bool isEnabled = true;
protected:
    Component(Entity* entity) {
        this->entity = entity;
    }
private:
    Entity* entity = nullptr;
    std::list<Component*> components;
};
