#include "Engine/Managers/ManagerHelper.hpp"
#include "Game/GameWorld.hpp"

GameWorld::GameWorld() {
    ManagerHelper::initialize("Asteroids", 1280, 800);
}

GameWorld::~GameWorld() {
    ManagerHelper::clean();
}

float GameWorld::getDeltaTime() {
    static long long int lastTime = 0;
    static long long int nowTime = SDL_GetPerformanceCounter();

    lastTime = nowTime;
    nowTime = SDL_GetPerformanceCounter();
    return (nowTime - lastTime) / performanceFrequency;
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
    ManagerHelper::render();
}
