#pragma once

#include "Engine/System/Node.hpp"
#include "Engine/Entities/Entity.hpp"
#include <string>

class Entity;

class Component : public Node {
public:
    virtual ~Component() = default;
    void setOwnerEntity(Entity* entityOwner);
    std::function<void()> onOwnerEntityChanged;
    
    const std::string& name;
protected:
    Component(const std::string& name = std::string());
private:
    Entity* entityOwner = nullptr;
    // TODO: identifier
};
