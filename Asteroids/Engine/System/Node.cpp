#include "Engine/Components/TransformComponent.hpp"
#include "Engine/System/Node.hpp"

Node::~Node() {
    for(Node* node : nodes) {
       if(node != nullptr) {
           delete node;
           node = nullptr;
       }
    }
    nodes.clear();
}

void Node::addNode(Node* node) {
    if(node != nullptr) {
        nodes.push_back(node);
        node->parentNode = this;
    }
}

Eigen::Vector2f Node::getPosition() const {
    TransformComponent* transformComponent = this->getNode<TransformComponent>();
    return transformComponent == nullptr ? Eigen::Vector2f(0, 0) : transformComponent->positionVector;
}

Eigen::Vector2f Node::getWorldPosition() const {
    Eigen::Vector2f position = this->getPosition();
    if(this->parentNode == nullptr) {
        return position;
    }
    
    Node* parentNode = this->getParentNode();
    while(parentNode != nullptr) {
        position += parentNode->getPosition();
        parentNode = parentNode->getParentNode();
    }
    return position;
}

void Node::setPosition(Eigen::Vector2f position) {
    TransformComponent* transformComponent = this->getNode<TransformComponent>();
    if(transformComponent == nullptr) {
        transformComponent = new TransformComponent();
        this->addNode(transformComponent);
    }
    
    transformComponent->positionVector = position;
}

Node* Node::getParentNode() const {
    return this->parentNode;
}

Eigen::Vector2f Node::getDimension() const {
    TransformComponent* transformComponent = this->getNode<TransformComponent>();
    return transformComponent == nullptr ? Eigen::Vector2f(0, 0) : transformComponent->dimensionVector;
}
