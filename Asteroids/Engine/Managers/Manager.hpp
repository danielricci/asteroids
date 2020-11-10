#pragma once

#include "Engine/Entities/Entity.hpp"
#include "Engine/System/Node.hpp"
#include <SDL.h>
#include <list>
#include <string>

class Manager {
public:
    Manager() = default;
    virtual ~Manager();
    
    virtual void update(float deltaTime);
    virtual void update(const SDL_Event& event);
    virtual void render(SDL_Renderer& renderer);
    
    void addNode(Node* node);
    void removeNode(Node* node);
    void clearNodes();
    
    template<typename T> T* getNode(std::string identifier = std::string()) const {
        T* myNode = nullptr;
        for(Node* node : nodes) {
            T* nodeCast = dynamic_cast<T*>(node);
            if(nodeCast != nullptr) {
                if(identifier.empty() || identifier == node->name) {
                    myNode = nodeCast;
                    break;
                }
            }
        }
        return myNode;
    }
    
    template<typename T> std::list<T*> getNodes() const {
        std::list<T*> nodes;
        for(Node* node : this->nodes) {
            T* myNode = dynamic_cast<T*>(node);
            if(myNode != nullptr) {
                nodes.push_back(myNode);
            }
        }
        return nodes;
    }
    
    void finish();
    
private:
    std::list<Node*> nodes;
    std::list<Node*> retiredNodes;
};
