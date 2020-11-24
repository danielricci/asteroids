#pragma once

#include <Eigen/Dense>
#include <list>
#include <string>

class Node {
public:
    virtual ~Node();
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
    
    Eigen::Vector2f getWorldPosition() const;
    virtual Eigen::Vector2f getPosition() const;
    virtual void setPosition(const Eigen::Vector2f& position);
    Eigen::Vector2f getOrigin() const;
    float getWorldOrientation() const;
    float getOrientation() const;
    void setOrientation(int orientation);
    virtual void setOrigin(const Eigen::Vector2f& position);
    virtual Eigen::Vector2f getDimension() const;
    
    std::string name;
protected:
    Node() = default;
    Node* getParentNode() const;
    void addNode(Node* node);
    
    std::function<void()> onParentNodeChanged;
private:
    std::list<Node*> nodes;
    Node* parentNode = nullptr;
};
