#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Managers/UIManager.hpp"
#include <iostream>

UIManager::~UIManager() {
    if(startMenuEntity != nullptr) {
        delete startMenuEntity;
        startMenuEntity = nullptr;
    }
}

void UIManager::render(SDL_Renderer &renderer) {
    startMenuEntity->render(renderer);
}

void UIManager::update(const SDL_Event& event) {
    switch(event.type) {
        case SDL_MOUSEMOTION:
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            startMenuEntity->update(event);
            SDL_Point point;
            point.x = event.motion.x;
            point.y = event.motion.y;
            
            SDL_Rect rectangle = startMenuEntity->getComponent<TransformComponent>()->getRectangle();
            if(SDL_PointInRect(&point, &rectangle)) {
                std::cout << "Mouse Entered" << std::endl;
            }
            break;
    }
}
