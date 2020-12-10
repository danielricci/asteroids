#pragma once

#include "Engine/Entities/Entity.hpp"
#include <string>

class Entity;

class Component {
public:
    virtual ~Component() = default;
    void setOwnerEntity(Entity* entityOwner);
    std::string name = "";
protected:
    Component() = default;
    Entity* ownerEntity = nullptr;
};
