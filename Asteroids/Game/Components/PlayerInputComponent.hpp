#pragma once

#include "Engine/Components/InputComponent.hpp"
#include "SDL.h"

class PlayerInputComponent final : public InputComponent {
public:
    enum class RotationAction {
        NONE = 0,
        ROTATE_LEFT,
        ROTATE_RIGHT
    };
    
    PlayerInputComponent();
    
    inline RotationAction getRotationAction() const {
        return rotationAction;
    }
    
    inline bool getIsThrustActivated() const {
        return isThrustActivated;
    }
    
    std::function<void()> eventOnThrustStart = nullptr;
    std::function<void()> eventOnThrustStop = nullptr;
    std::function<void()> eventOnHyperspace = nullptr;
    std::function<void()> eventOnShoot = nullptr;
    
private:
    bool isThrustActivated = false;
    
    void onRotate(const SDL_Event& event);
    void onThrust(const SDL_Event& event);
    void onHyperspace(const SDL_Event& event);
    void onShoot(const SDL_Event& event);
    
    RotationAction rotationAction = RotationAction::NONE;
};
