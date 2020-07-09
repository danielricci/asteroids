#pragma once

#include "Engine/System/Node.hpp"
#include <Eigen/Dense>
#include <list>

class Component : public Node {
public:
    virtual ~Component();
    template<typename T> T* getComponent() {
        T* myComponent = nullptr;
        for(Component* component : components) {
            if((myComponent = dynamic_cast<T*>(component)) != nullptr) {
                break;
            }
        }
        return myComponent;
    }
    
    void addComponent(Component* component);
    void setPosition(const Eigen::Vector2f& position);    
protected:
    Component() = default;
private:
    std::list<Component*> components;
};
