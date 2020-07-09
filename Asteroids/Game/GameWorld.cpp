#include "Engine/Components/TextRenderComponent.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Engine/Managers/UIManager.hpp"
#include "Game/GameWindow.hpp"
#include "Game/Entities/MainMenuEntity.hpp"

GameWorld::GameWorld(SDL_Window& window, SDL_Renderer& renderer) : window(window), renderer(renderer) {
    initialize();
}

GameWorld::~GameWorld() {
    destroy();
}

void GameWorld::clean() {
    ManagerHelper::clean();
}

void GameWorld::destroy() {
    clean();
}

void GameWorld::initialize() {
    ManagerHelper::initialize();
}

void GameWorld::run() {
    isRunning = true;
    while(isRunning) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            update(event);
        }
        if(isRunning) {
            update(gameWorldClock.sample());
            render();
        }
    }
}

void GameWorld::update(const SDL_Event& event) {
    switch(event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default: {
            ManagerHelper::update(event);
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
    deltaTime = deltaTime; // Just to shut up xcode
}

void GameWorld::render() const {
    SDL_SetRenderDrawColor(&renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(&renderer);
    SDL_SetRenderDrawColor(&renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    ManagerHelper::render(renderer);
    SDL_RenderPresent(&renderer);
}
