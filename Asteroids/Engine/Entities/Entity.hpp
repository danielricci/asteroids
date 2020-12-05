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
    
    template<typename T> T* getComponent(const std::string& name = std::string()) const;
    template<typename T> std::list<T*> getComponents() const;
    
    virtual Eigen::Vector2f getPosition() const;
    virtual void setPosition(const Eigen::Vector2f& position);
    
    float getOrientation() const;
    void setOrientation(int orientation);
    
    Eigen::Vector2f getOrigin() const;
    virtual void setOrigin(const Eigen::Vector2f& position);
    
    void setDimension(const Eigen::Vector2f& dimension) const;
    virtual Eigen::Vector2f getDimension() const;

    virtual void render(SDL_Renderer& renderer) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void update(const SDL_Event& event) = 0;
protected:
    Entity();
private:
    std::list<Component*> components;
};
