#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Managers/UIManager.hpp"
#include <iostream>

UIManager::~UIManager() {
    if(mainMenuEntity != nullptr) {
        delete mainMenuEntity;
        mainMenuEntity = nullptr;
    }
}

void UIManager::render(SDL_Renderer &renderer) {
    mainMenuEntity->render(renderer);
}

void UIManager::update(const SDL_Event& event) {
    switch(event.type) {
        case SDL_MOUSEMOTION:
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            mainMenuEntity->update(event);
            SDL_Point point;
            point.x = event.motion.x;
            point.y = event.motion.y;
            
            SDL_Rect rectangle = mainMenuEntity->getComponent<TransformComponent>()->getRectangle();
            if(SDL_PointInRect(&point, &rectangle)) {
                std::cout << "Mouse Entered" << std::endl;
            }
            break;
    }
}
