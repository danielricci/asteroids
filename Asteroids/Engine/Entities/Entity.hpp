#pragma once

#include "Engine/Components/Component.hpp"
#include <Eigen/Dense>
#include <SDL.h>
#include <string>

class Component;

class Entity {
public:
    void addComponent(Component* Component);
    template<typename T> T* getComponent(std::string name = std::string()) const;// {
//        T* resultComponent = nullptr;
//        for(Component* component : components) {
//            T* componentCast = dynamic_cast<T*>(component);
//            if(componentCast != nullptr) {
//                if(name.empty() || name == component->name) {
//                    resultComponent = componentCast;
//                    break;
//                }
//            }
//        }
//        return resultComponent;
//    }
    
    virtual void render(SDL_Renderer& renderer) = 0;
    virtual void setPosition(const Eigen::Vector2f& position);
    virtual void update(float deltaTime) = 0;
    virtual void update(const SDL_Event& event) = 0;
protected:
    Entity();
private:
    std::list<Component*> components;
    // TODO: identifier
};
