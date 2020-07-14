#pragma once

#include "Engine/System/Node.hpp"
#include <Eigen/Dense>

class Component : public Node {
public:
    virtual ~Component() = default;
protected:
    Component() = default;
};
