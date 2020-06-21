#pragma once

#include "Engine/Components/Component.hpp"

#include <list>

class Component;

class Entity {
public:
    virtual ~Entity();
    
    template<typename T> T* getComponent() const {
        T* myComponent = nullptr;
        for(Component* component : components) {
            if((myComponent = dynamic_cast<T*>(component)) != nullptr) {
                break;
            }
        }
        return myComponent;
    }
    
    Component* addComponent(Component* component);
protected:
    Entity(int x = 0, int y = 0, int width = 0, int height = 0);
private:
    std::list<Component*> components;
};
