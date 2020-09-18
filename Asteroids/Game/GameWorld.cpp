#include "Game/Entities/MainMenuEntity.hpp"
#include "Game/Entities/PlayerEntity.hpp"
#include "Game/GameWorld.hpp"
#include "Engine/Managers/GameManager.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Engine/Managers/UIManager.hpp"
#include "Engine/System/Engine.hpp"

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
    ManagerHelper::get<UIManager>()->addEntity(new MainMenuEntity());
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
            if(event.type == SDL_USEREVENT) {
                SDL_UserEvent userEvent = event.user;
                switch(userEvent.code) {
                    case static_cast<int>(Engine::EngineEvents::EVENT_ENGINE_START_GAME): {
                        this->constructGameWorld();
                        break;
                    }
                }
            }
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

void GameWorld::constructGameWorld() {
    PlayerEntity* playerEntity = new PlayerEntity();
    int width = 0;
    int height = 0;
    SDL_GetWindowSize(&window, &width, &height);
    playerEntity->setPosition({width/2, height/2});
    ManagerHelper::get<GameManager>()->addEntity(playerEntity);
}
