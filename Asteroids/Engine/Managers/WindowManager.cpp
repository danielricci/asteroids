#include "Engine/Managers/WindowManager.hpp"
#include <iostream>

WindowManager::WindowManager(const char* const title, int width, int height) {
    if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL video initialization failed: " << SDL_GetError() << std::endl;
        return;
    }
    
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if(window == nullptr) {
        std::cerr << "SDL window could not be created: " << SDL_GetError() << std::endl;
        return;
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == nullptr) {
        std::cerr << "SDL renderer could not be created: " << SDL_GetError() << std::endl;
        return;
    }
}

WindowManager::~WindowManager() {
    if(window != nullptr) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    
    if(renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

SDL_Renderer* WindowManager::getRenderer() const {
    return renderer;
}

SDL_Rect WindowManager::getWindowSize() {
    SDL_Rect rectangle;
    rectangle.x = 0;
    rectangle.y = 0;
    SDL_GetWindowSize(window, &rectangle.w, &rectangle.h);
    return rectangle;
}
