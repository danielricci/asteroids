#pragma once

#include "Engine/Components/InputComponent.hpp"
#include "SDL.h"

class PlayerInputComponent : public InputComponent {
public:
    enum class PlayerAction {
        NONE = 0,
        ROTATE_LEFT,
        ROTATE_RIGHT,
        THRUST,
        HYPERSPACE
    };
    
    PlayerInputComponent();
    PlayerAction getRotationAction() const;
    PlayerAction getMovementAction() const;
    
    void reset();
private:
    void onRotate(const SDL_Event& event);
    void onThrust(const SDL_Event& event);
    void onHyperspace(const SDL_Event& event);
    
    PlayerAction rotationAction = PlayerAction::NONE;
    PlayerAction movementAction = PlayerAction::NONE;
};
