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
        std::uniform_int_distribution<int> orientationDistribution(static_cast<int>(TransformComponent::ORIENTATION_ORIGIN), static_cast<int>(TransformComponent::ORIENTATION_FULL_ROTATION));
        std::mt19937 generator(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
        return orientationDistribution(generator);
    }
    
    static const int ORIENTATION_ORIGIN = 0;
    static const int ORIENTATION_NORTH_EAST = -45;
    static const int ORIENTATION_NORTH = -90;
    static const int ORIENTATION_WEST = -180;
    static const int ORIENTATION_SOUTH = -270;
    static const int ORIENTATION_FULL_ROTATION = -360;
    
    int orientation = 0;
    Eigen::Vector2f origin { 0, 0 };
    Eigen::Vector2f dimension { 0, 0 };
    Eigen::Vector2f position { 0, 0 };
    Eigen::Vector2f velocity { 0, 0 };
};
