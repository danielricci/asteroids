#pragma once

#include "Engine/Entities/Entity.hpp"
#include <Eigen/Dense>
#include <string>

class Entity;

class Component {
public:
    virtual ~Component() = default;
    void setOwnerEntity(Entity* entityOwner);
    std::function<void()> onOwnerEntityChanged;
    const std::string& name;
protected:
    Component(const std::string& name = std::string());
private:
    Entity* ownerEntity = nullptr;
};
