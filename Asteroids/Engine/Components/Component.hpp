#pragma once

#include <Eigen/Dense>
#include <list>

class Component {
public:
    virtual ~Component();
    template<typename T> T* get() const {
        T* myComponent = nullptr;
        for(Component* component : components) {
            if((myComponent = dynamic_cast<T*>(component)) != nullptr) {
                break;
            }
        }
        return myComponent;
    }
    template<typename T> std::list<T*> getAll() const {
        std::list<T*> componentList;
        for(Component* component : components) {
            T* myComponent = dynamic_cast<T*>(component);
            if(myComponent != nullptr) {
                componentList.push_back(component);
            }
        }
        return componentList;
    }
    void addComponent(Component* component);
    
protected:
    Component() = default;
private:
    std::list<Component*> components;
};
