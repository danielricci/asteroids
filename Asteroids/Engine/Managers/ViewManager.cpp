#include "Engine/Managers/ViewManager.hpp"
#include <iostream>
#include <SDL_ttf.h>

ViewManager::ViewManager(const std::initializer_list<View*>& views) {
    if(TTF_Init() < 0) {
        std::cerr << "SDL_ttf could not be initialized: " << TTF_GetError() << std::endl;
    }
    
    for(auto& view : views) {
        this->addEntity(view);
    }
}

ViewManager::~ViewManager() {
    // Hack: Prevent the base class from having anything to clear, TTF_QUIT must be called last
    clean();
    TTF_Quit();
}

void ViewManager::render(SDL_Renderer& renderer) {
    if(activeView != nullptr) {
        activeView->render(renderer);
    }
}

void ViewManager::setActiveView(const std::string& viewName) {
    for(auto& pair : entities) {
        View* view = dynamic_cast<View*>(pair.first);
        if(view != nullptr && view->getViewName() == viewName) {
            activeView = view;
            break;
        }
    }
}

void ViewManager::update(float deltaTime) {
    if(activeView != nullptr) {
        activeView->update(deltaTime);
    }
}

void ViewManager::update(const SDL_Event& event) {
    if(activeView != nullptr) {
        activeView->update(event);
    }
}
