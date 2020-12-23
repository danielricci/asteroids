#pragma once

#include "Engine/Components/Component.hpp"
#include <Eigen/Dense>
#include <list>
#include <SDL.h>
#include <string>

class Component;

class Entity {
public:
    virtual ~Entity();
    
    void addComponent(Component* Component);
    template<typename T> bool hasComponent(const std::string& name = std::string()) const {
        return this->getComponent<T>(name) != nullptr;
    }

    virtual Eigen::Vector2f getPosition() const;
    virtual void setPosition(const Eigen::Vector2f& position);
    
    float getOrientation() const;
    void setOrientation(int orientation);
    
    Eigen::Vector2f getOrigin() const;
    virtual void setOrigin(const Eigen::Vector2f& position);
    
    void setDimension(const Eigen::Vector2f& dimension) const;
    virtual Eigen::Vector2f getDimension() const;
    virtual SDL_Rect getEntityBounds() const;

    virtual void collision(Entity& entity) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void update(const SDL_Event& event) = 0;
    virtual void render(SDL_Renderer& renderer) = 0;
protected:
    Entity();
    template<typename T> T* getComponent(const std::string& name = std::string()) const {
        T* result = nullptr;
        for(Component* component : components) {
            T* cast = dynamic_cast<T*>(component);
            if(cast != nullptr) {
                if(name.empty() || name == cast->name) {
                    result = cast;
                    break;
                }
            }
        }
        
        return result;
    }
    template<typename T> std::list<T*> getComponents() const {
        std::list<T*> components;
        for(Component* component : this->components) {
            T* cast = dynamic_cast<T*>(component);
            if(cast != nullptr) {
                components.push_back(cast);
            }
        }
        return components;
    }
private:
    std::list<Component*> components;
};
