#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Managers/UIManager.hpp"
#include <iostream>

UIManager::UIManager(SDL_Renderer& renderer) : renderer(renderer) {
}

UIManager::~UIManager() {
    if(startMenuEntity != nullptr) {
        delete startMenuEntity;
        startMenuEntity = nullptr;
    }
}

void UIManager::processEvent(const SDL_Event& event) {
    switch(event.type) {
        case SDL_MOUSEMOTION:
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            startMenuEntity->processEvent(event);
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
