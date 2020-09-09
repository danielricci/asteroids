#pragma once

#include "Engine/Components/InputComponent.hpp"
#include "SDL.h"

class PlayerInputComponent : public InputComponent {
public:
    enum class PlayerAction {
        NONE = 0,
        ROTATE_LEFT,
        ROTATE_RIGHT,
        THRUST
    };
    
    PlayerInputComponent();
    PlayerAction getRotationAction() const;
    PlayerAction getThrustAction() const;
private:
    void onRotate(const SDL_Event& event);
    void onThrust(const SDL_Event& event);
    
    PlayerAction rotationAction = PlayerAction::NONE;
    PlayerAction thrustAction = PlayerAction::NONE;
};
