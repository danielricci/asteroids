#include "Engine/Managers/GameManager.hpp"
#include "Engine/Managers/InputManager.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Engine/Managers/SoundManager.hpp"
#include "Engine/Managers/UIManager.hpp"
#include "Engine/Managers/WindowManager.hpp"
#include <SDL.h>

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

void ManagerHelper::finish() {
    for(Manager* manager : managers) {
        if(manager != nullptr) {
            manager->finish();
        }
    }
}

void ManagerHelper::initialize(const char* const title, int width, int height) {
    clean();
    managers.push_back(new WindowManager(title, width, height));
    managers.push_back(new GameManager());
    managers.push_back(new InputManager());
    managers.push_back(new UIManager());
    managers.push_back(new SoundManager());
}

void ManagerHelper::render() {
    SDL_Renderer* renderer = getRenderer();
    for(Manager* manager : managers) {
        if(manager != nullptr) {
            manager->render(*renderer);
        }
    }
}

void ManagerHelper::update(float deltaTime) {
    for(Manager* manager : managers) {
        if(manager != nullptr) {
            manager->update(deltaTime);
        }
    }
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
