#pragma once

#include "Engine/Components/Component.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include <Eigen/Dense>
#include <SDL.h>
#include <list>

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
    template<typename T> std::list<T*> getAllComponents() const {
        std::list<T*> components;
        for(Component* component : this->components) {
            T* myComponent = dynamic_cast<T*>(component);
            if(myComponent != nullptr) {
                components.push_back(myComponent);
            }
        }
        return components;
    }
    
    virtual void update(const SDL_Event& event);
    void addComponent(Component* component);
    void setPosition(float x, float y);
protected:
    Entity();
private:
    std::list<Component*> components;
};
