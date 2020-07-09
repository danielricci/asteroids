#include "Engine/System/Node.hpp"

std::map<Node::NodeIdentifier, Node*> Node::mappings;
Node::NodeIdentifier Node::nodeIdentifierCounter = 0;

Node::Node() : nodeIdentifier(++nodeIdentifierCounter) {
    mappings[nodeIdentifier] = this;
}

Node::~Node() {
    std::map<Node::NodeIdentifier, Node*>::iterator it = mappings.find(nodeIdentifier);
    if(it != mappings.end()) {
        mappings.erase(it);
    }
}

Node* Node::getParentNode() const {
    std::map<Node::NodeIdentifier, Node*>::iterator it = mappings.find(parentNodeIdentifier);
    return it == mappings.end() ? nullptr : it->second;
}

void Node::setParentNode(Node* parentNode) {
    if(parentNode != nullptr) {
        this->parentNodeIdentifier = parentNode->nodeIdentifier;
    }
}
