#pragma once

#include "Engine/Entities/Entity.hpp"
#include <SDL.h>
#include <list>

class Manager {
public:
    virtual ~Manager();
    
    virtual void update(float deltaTime);
    virtual void update(const SDL_Event& event);
    virtual void render(SDL_Renderer& renderer);
    
    void addEntity(Entity* entity);
    void clearEntities();
    
//    template<typename T> T* getEntity(std::string identifier = std::string()) const {
//        T* myNode = nullptr;
//        for(Node* node : nodes) {
//            T* nodeCast = dynamic_cast<T*>(node);
//            if(nodeCast != nullptr) {
//                if(identifier.empty() || identifier == node->name) {
//                    myNode = nodeCast;
//                    break;
//                }
//            }
//        }
//        return myNode;
//    }
//
//    template<typename T> std::list<T*> getNodes() const {
//        std::list<T*> nodes;
//        for(Node* node : this->nodes) {
//            T* myNode = dynamic_cast<T*>(node);
//            if(myNode != nullptr) {
//                nodes.push_back(myNode);
//            }
//        }
//        return nodes;
//    }
    
protected:
    Manager() = default;
private:
    std::list<Entity*> entities;
};
