#pragma once

#include "Engine/Components/InputComponent.hpp"
#include "SDL.h"

class PlayerInputComponent : public InputComponent {
public:
    enum class PlayerAction {
        NONE = 0,
        ROTATE_LEFT,
        ROTATE_RIGHT
    };
    PlayerAction getPlayerAction() const;
    PlayerInputComponent();
private:
    void onRotate(const SDL_Event& event);
    PlayerAction playerAction = PlayerAction::NONE;
};
