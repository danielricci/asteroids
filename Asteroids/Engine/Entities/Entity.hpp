#pragma once

#include <Eigen/Dense>
#include <list>
#include <SDL.h>
#include <string>

class Component;

class Entity {
public:
    virtual ~Entity();
    
    virtual void collisionCheck(Entity& entity) = 0;
    virtual Eigen::AlignedBox2f getBounds() const = 0;
    virtual void render(SDL_Renderer& renderer) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void update(const SDL_Event& event) = 0;

    void addComponent(Component* Component);
    std::list<Component*> getComponents();
    virtual Eigen::Vector2f getDimensions() const;
    float getOrientation() const;
    virtual Eigen::Vector2f getPosition() const;
    Eigen::Vector2f getPosition(const Eigen::Vector2f& vertex, bool includeWorldPosition = true) const;
    virtual void setDimensions(const Eigen::Vector2f& dimensions);
    void setOrientation(int orientation);
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
