#include "Engine/Managers/InputManager.hpp"

#include "Game/GameWindow.hpp"

GameWorld::GameWorld(SDL_Window& window, SDL_Renderer& renderer) : window(window), renderer(renderer) {
    InputManager::getInstance();
    initialize();
}

GameWorld::~GameWorld() {
    destroy();
}

void GameWorld::clean() {
    for(Entity* entity : entities) {
        if(entity != nullptr) {
            delete entity;
            entity = nullptr;
        }
    }
    entities.clear();
}

void GameWorld::destroy() {
    clean();
    delete InputManager::getInstance();
}

void GameWorld::initialize() {
}

void GameWorld::run() {
    isRunning = true;
    while(isRunning) {
        processInput();
        if(isRunning) {
            update(gameWorldClock.sample());
            render();
        }
    }
}

void GameWorld::processInput() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
            isRunning = false;
            break;
        }
    }
}

void GameWorld::update(float deltaTime) const {
    // For now values of delta times that are greater than 1
    // or less than 120hz are clamped to 1/60. Issues arise when
    // the application first opens, and when the window is fully behind
    // another window, the deltaTime gets very very fast
    if(deltaTime < 0.0083 || deltaTime > 1) {
        deltaTime = 1.f / 60.f;
    }
}

void GameWorld::render() const {
    SDL_SetRenderDrawColor(&renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(&renderer);
    SDL_RenderPresent(&renderer);
}
