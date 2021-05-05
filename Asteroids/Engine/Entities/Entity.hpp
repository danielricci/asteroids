#pragma once

#include <Eigen/Dense>
#include <list>
#include <SDL.h>
#include <string>

class Component;

class Entity {
public:
    virtual ~Entity();
    
    // TODO: Put into the game entity ================
    virtual Eigen::AlignedBox2f getBounds() const {
        return Eigen::AlignedBox2f();
    }
    // ===============================================

    // TODO: Put this into its own interface ==========
    virtual void render(SDL_Renderer& renderer) {
    }
    virtual void update(float deltaTime) {
    }
    virtual void update(const SDL_Event& event) {
    }
    // ================================================

    void addComponent(Component* Component);
    std::list<Component*> getComponents();
    virtual Eigen::Vector2f getDimensions() const;
    float getOrientation() const;
    virtual Eigen::Vector2f getPosition() const;
    Eigen::Vector2f getWorldPosition(const Eigen::Vector2f& vertex, bool includeWorldPosition = true) const;
    virtual void setDimensions(const Eigen::Vector2f& dimensions);
    virtual void setOrientation(int orientation);
    virtual void setPosition(const Eigen::Vector2f& position);
    
    template<typename T> T* getComponent(const std::string& name = std::string()) const {
        T* result = nullptr;
        for(Component* component : components) {
            T* cast = dynamic_cast<T*>(component);
            if(cast != nullptr) {
                if(name.empty() || name == cast->getName()) {
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
    template<typename T> bool hasComponent(const std::string& name = std::string()) const {
        return this->getComponent<T>(name) != nullptr;
    }
protected:
    Entity();
private:
    std::list<Component*> components;
};
