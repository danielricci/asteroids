#pragma once

#include "Engine/System/Node.hpp"
#include <Eigen/Dense>

class Component : public Node {
public:
    virtual ~Component() = default;
    void setOffsetPosition(float x, float y);
protected:
    Component() = default;
private:
    Eigen::Vector2f offsetPosition;
};
