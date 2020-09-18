#pragma once

#include "Engine/Managers/Manager.hpp"
#include <SDL.h>

class GameSettingsManager : public Manager {
public:
    GameSettingsManager(SDL_Window& window);
    void getWindowSize(int& width, int& height) const;
private:
    SDL_Window& window;
};
