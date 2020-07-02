#include "Engine/Managers/InputManager.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Engine/Managers/UIManager.hpp"

std::list<Manager*> ManagerHelper::managers {};

void ManagerHelper::clean() {
    for(Manager* manager : managers) {
        if(manager != nullptr) {
            delete manager;
            manager = nullptr;
        }
    }
    managers.clear();
}

void ManagerHelper::initialize(SDL_Renderer& renderer) {
    clean();
    managers.push_back(new InputManager());
    managers.push_back(new UIManager(renderer));
}

void ManagerHelper::processEvent(const SDL_Event& event) {
    for(Manager* manager : managers) {
        if(manager != nullptr) {
            manager->processEvent(event);
        }
    }
}
