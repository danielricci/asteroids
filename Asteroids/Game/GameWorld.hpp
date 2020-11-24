#pragma once

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

    float getDeltaTime();
    
    SDL_Renderer& renderer;
    
    bool isRunning = false;

    const float deltaTimeClamp = 1.f / 60.f;
    const float minDeltaTime = 1.f / 120.f;
    const float maxDeltaTime = 1.f;
};
