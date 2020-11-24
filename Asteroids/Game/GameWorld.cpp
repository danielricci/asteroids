#include "Engine/Managers/GameManager.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Game/GameWorld.hpp"

GameWorld::GameWorld(SDL_Window& window, SDL_Renderer& renderer) : renderer(renderer) {
    ManagerHelper::initialize(window);
    ManagerHelper::get<GameManager>()->setGameState(GameManager::GameState::STARTED);
}

GameWorld::~GameWorld() {
    ManagerHelper::clean();
}

float GameWorld::getDeltaTime() {
    static long long int lastTime = 0;
    static long long int nowTime = 0;

    if(nowTime == 0) {
        nowTime = SDL_GetPerformanceCounter();
    }
    lastTime = nowTime;
    nowTime = SDL_GetPerformanceCounter();
    return (nowTime - lastTime) / static_cast<float>(SDL_GetPerformanceFrequency());
}

void GameWorld::run() {
    isRunning = true;
    while(isRunning) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            update(event);
        }
        if(isRunning) {
            update(getDeltaTime());
            render();
        }
        ManagerHelper::finish();
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
