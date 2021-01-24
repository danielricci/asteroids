#pragma once

#include "Engine/Components/Component.hpp"
#include <Eigen/Dense>
#include <random>

class TransformComponent final : public Component {
public:
    TransformComponent() = default;
    
    static float toRadians(float degrees) {
        return degrees * M_PI/180;
    }
    
    static int getRandomRotation() {
        std::uniform_int_distribution<int> rotationDistribution(static_cast<int>(TransformComponent::ROTATION_RIGHT), static_cast<int>(TransformComponent::ROTATION_FULL_UNIT));
        std::mt19937 generator(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
        return rotationDistribution(generator);
    }
       
    static const int ROTATION_RIGHT = 0;
    static const int ROTATION_TOP_RIGHT = -45;
    static const int ROTATION_TOP = -90;
    static const int ROTATION_LEFT = -180;
    static const int ROTATION_DOWN = -270;
    static const int ROTATION_FULL_UNIT = -360;
    
    int orientation = 0;
    Eigen::Vector2f position { 0, 0 };    
};
