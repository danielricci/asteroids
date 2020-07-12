#pragma once

#include "Engine/Components/Component.hpp"
#include <Eigen/Dense>
#include <SDL.h>
#include <list>

class Component;

class Entity {
public:
    virtual ~Entity();
    template<typename T> T* get() const {
        T* myComponent = nullptr;
        for(Component* component : components) {
            if((myComponent = dynamic_cast<T*>(component)) != nullptr) {
                break;
            }
        }
        return myComponent;
    }
    
    virtual void update(const SDL_Event& event);
    void addComponent(Component* component);
        
protected:
    Entity();
private:
    std::list<Component*> components;
};
