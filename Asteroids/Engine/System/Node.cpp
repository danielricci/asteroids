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

void Node::setPosition(Eigen::Vector2f position) {
    TransformComponent* transformComponent = this->getNode<TransformComponent>();
    if(transformComponent != nullptr) {
        transformComponent->positionVector = position;
    }
}
