#include "Game/Entities/MainMenuEntity.hpp"
#include "Game/GameWorld.hpp"
#include "Engine/Managers/GameManager.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Engine/Managers/UIManager.hpp"

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
    ManagerHelper::initialize(window);
    ManagerHelper::get<UIManager>()->addNode(new MainMenuEntity());
    
    // TODO - Remove me to re-enable menu
    ManagerHelper::get<GameManager>()->setGameState(GameManager::GameState::STARTED);
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
    if(deltaTime < minDeltaTime || deltaTime > maxDeltaTime) {
        deltaTime = deltaTimeClamp;
    }
    ManagerHelper::update(deltaTime);
}

void GameWorld::render() const {
    SDL_SetRenderDrawColor(&renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(&renderer);
    SDL_SetRenderDrawColor(&renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    ManagerHelper::render(renderer);
    SDL_RenderPresent(&renderer);
}
