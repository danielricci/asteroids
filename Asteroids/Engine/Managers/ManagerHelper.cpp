#include "Engine/Managers/GameManager.hpp"
#include "Engine/Managers/GameSettingsManager.hpp"
#include "Engine/Managers/InputManager.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Engine/Managers/SoundManager.hpp"
#include "Engine/Managers/UIManager.hpp"

std::list<Manager*> ManagerHelper::managers {};

ManagerHelper::~ManagerHelper() {
    clean();
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

void ManagerHelper::initialize(SDL_Window& window) {
    clean();
    managers.push_back(new GameManager());
    managers.push_back(new InputManager());
    managers.push_back(new GameSettingsManager(window));
    managers.push_back(new UIManager());
    managers.push_back(new SoundManager());
}

void ManagerHelper::render(SDL_Renderer &renderer) {
    for(Manager* manager : managers) {
        if(manager != nullptr) {
            manager->render(renderer);
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
