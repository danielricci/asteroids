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
    
    static int getRandomOrientation() {
        std::uniform_int_distribution<int> orientationDistribution(static_cast<int>(TransformComponent::ORIENTATION_RIGHT), static_cast<int>(TransformComponent::ORIENTATION_FULL_UNIT));
        std::mt19937 generator(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
        return orientationDistribution(generator);
    }
    
    static const int ORIENTATION_RIGHT = 0;
    static const int ORIENTATION_TOP_RIGHT = -45;
    static const int ORIENTATION_TOP = -90;
    static const int ORIENTATION_LEFT = -180;
    static const int ORIENTATION_DOWN = -270;
    static const int ORIENTATION_FULL_UNIT = -360;
    
    int orientation = 0;
    Eigen::Vector2f origin { 0, 0 };
    Eigen::Vector2f dimension { 0, 0 };
    Eigen::Vector2f position { 0, 0 };
    Eigen::Vector2f velocity { 0, 0 };
};
