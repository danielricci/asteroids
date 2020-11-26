#pragma once

#include "Engine/Managers/Manager.hpp"
#include <SDL.h>

class WindowManager final : public Manager {
public:
    WindowManager(const char* const title, int width, int height);
    ~WindowManager();
    
    SDL_Rect getWindowSize();
    inline SDL_Renderer* getRenderer() const {
        return renderer;
    }
    
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};
