#pragma once

#include <map>

class Node {
public:
    virtual ~Node();    
protected:
    Node();
    Node* getParentNode() const;
    void setParentNode(Node* parentNode);
private:

    // ---------------------------------------------------------
    typedef unsigned long long int NodeIdentifier;
    static std::map<NodeIdentifier, Node*> mappings;
    static NodeIdentifier nodeIdentifierCounter;
    const NodeIdentifier nodeIdentifier = 0;
    NodeIdentifier parentNodeIdentifier = 0;
    // TODO: Do we need NodeIdentifier or can the parent just simply be a Node*
    // ---------------------------------------------------------
    
};
