#include "Engine/Managers/GameManager.hpp"
#include "Engine/Managers/InputManager.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Engine/Managers/WindowManager.hpp"
#include <SDL.h>
#include <set>

std::list<Manager*> ManagerHelper::managers {};

ManagerHelper::~ManagerHelper() {
    clean();
    SDL_Quit();
}

void ManagerHelper::clean() {
    for(Manager* manager : managers) {
        if(manager != nullptr) {
            delete manager;
            manager = nullptr;
        }
    }
    managers.clear();
}

void ManagerHelper::clean(Entity* entity) {
    if(entity != nullptr) {
        for(Manager* manager : managers) {
            if(manager != nullptr) {
                manager->clean(entity);
            }
        }
    }
}

void ManagerHelper::initialize(const char* const title, int width, int height) {
    clean();
    managers.push_back(new WindowManager(title, width, height));
    GameManager* gameManager = new GameManager();
    gameManager->setGameState(GameManager::GameState::STARTED);
    managers.push_back(gameManager);
    managers.push_back(new InputManager());
}

void ManagerHelper::render() {
    SDL_Renderer* renderer = ManagerHelper::getRenderer();
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    for(Manager* manager : managers) {
        if(manager != nullptr) {
            manager->render(*renderer);
        }
    }
    SDL_RenderPresent(renderer);
}

void ManagerHelper::update(float deltaTime) {
    for(Manager* manager : managers) {
        if(manager != nullptr) {
            manager->update(deltaTime);
        }
    }
    
    for(Manager* manager : managers) {
        if(manager != nullptr) {
            manager->collision();
        }
    }
    
    std::set<Entity*> entitiesToDelete;
    for(Manager* manager : managers) {
        if(manager != nullptr) {
            auto flushedEntities = manager->flush();
            std::copy(flushedEntities.begin(), flushedEntities.end(), std::inserter(entitiesToDelete, entitiesToDelete.begin()));
        }
    }
    std::for_each(entitiesToDelete.begin(), entitiesToDelete.end(), [](Entity* entity) {
        delete entity;
    });
}

void ManagerHelper::update(const SDL_Event& event) {
    for(Manager* manager : managers) {
        if(manager != nullptr) {
            manager->update(event);
        }
    }
}

SDL_Renderer* ManagerHelper::getRenderer() {
    return get<WindowManager>()->getRenderer();
}
