#pragma once

#include <Eigen/Dense>

class Component {
public:
    virtual ~Component() = default;
    void setOffsetPosition(float x, float y);
protected:
    Component() = default;
private:
    Eigen::Vector2f offsetPosition;
};
