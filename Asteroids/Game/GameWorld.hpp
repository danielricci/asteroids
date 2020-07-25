#pragma once

#include "Engine/Core/Clock.hpp"
#include <SDL.h>

class GameWorld {
public:
    GameWorld(SDL_Window& window, SDL_Renderer& renderer);
    ~GameWorld();
    
    void run();
private:
    void update(const SDL_Event& event);
    void update(float deltaTime) const;
    void render() const;
    
    void clean();
    void destroy();
    void initialize();

    SDL_Window& window;
    SDL_Renderer& renderer;
    
    Clock gameWorldClock;
    
    bool isRunning = false;
};
