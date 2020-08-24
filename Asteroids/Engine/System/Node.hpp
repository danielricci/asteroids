#pragma once

#include <Eigen/Dense>
#include <list>

class Node {
public:
    virtual ~Node();
    template<typename T> T* getNode() const {
        T* myNode = nullptr;
        for(Node* node : nodes) {
            if((myNode = dynamic_cast<T*>(node)) != nullptr) {
                break;
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
    virtual void setOrigin(const Eigen::Vector2f& position);
    virtual Eigen::Vector2f getDimension() const;
protected:
    Node() = default;
    Node* getParentNode() const;
    void addNode(Node* node);
private:
    std::list<Node*> nodes;
    Node* parentNode = nullptr;
};
