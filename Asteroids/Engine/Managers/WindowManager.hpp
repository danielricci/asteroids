#pragma once

#include "Engine/Managers/Manager.hpp"
#include <SDL.h>

class WindowManager final : public Manager {
public:
    WindowManager();
    ~WindowManager();
    
    SDL_Rect getWindowSize();
    SDL_Renderer* getRenderer() const;
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};
