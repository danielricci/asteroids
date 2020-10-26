#pragma once

#include "Engine/Components/InputComponent.hpp"
#include "SDL.h"
#include <string>

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
    PlayerAction getMovementAction() const;
    
    void reset();
    
    static inline const std::string EVENT_SHOOT = "EVENT_SHOOT";
    static inline const std::string EVENT_HYPERSPACE = "EVENT_HYPERSPACE";
    static inline const std::string EVENT_THRUST = "EVENT_THRUST";
    static inline const std::string EVENT_ROTATE_LEFT = "EVENT_ROTATE_LEFT";
    static inline const std::string EVENT_ROTATE_RIGHT = "EVENT_ROTATE_RIGHT";
    
private:
    void onRotate(const SDL_Event& event);
    void onThrust(const SDL_Event& event);
    
    PlayerAction rotationAction = PlayerAction::NONE;
    PlayerAction movementAction = PlayerAction::NONE;
};
