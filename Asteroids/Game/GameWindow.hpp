#pragma once

#include "Game/GameWorld.hpp"

#include <SDL.h>

class GameWindow {
public:
    GameWindow(const char* title, int width, int height);
    ~GameWindow();
    void show() const;
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    
    GameWorld* gameWorld = nullptr;
};
