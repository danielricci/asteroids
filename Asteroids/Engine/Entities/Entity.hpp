#pragma once

#include "Engine/Components/Component.hpp"
#include "Engine/System/Node.hpp"
#include <SDL.h>
#include <list>

class Component;

class Entity : public Node {
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
    
    virtual void update(const SDL_Event& event);
    Component* addComponent(Component* component);
protected:
    Entity();
private:
    std::list<Component*> components;
};
