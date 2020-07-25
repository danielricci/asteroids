#pragma once

#include "Engine/System/Node.hpp"

class Component : public Node {
public:
    virtual ~Component() = default;
protected:
    Component() = default;
};
