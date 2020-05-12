#pragma once

#include "Game/Components/InputComponent.hpp"

#include <Eigen/Dense>

class SnakeInputComponent : public InputComponent {
public:
    SnakeInputComponent(GameObject* gameObject);
    inline Eigen::Vector2f getInputVector() const {
        return inputVector;
    }
private:
    void onMove(const SDL_Event& event);
    
    const std::string ACTION_MOVE = "Move";
    Eigen::Vector2f inputVector { 1, 0 };
};
