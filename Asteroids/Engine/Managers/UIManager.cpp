#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Managers/UIManager.hpp"

UIManager::~UIManager() {
//    if(mainMenuEntity != nullptr) {
//        delete mainMenuEntity;
//        mainMenuEntity = nullptr;
//    }
}

void UIManager::render(SDL_Renderer &renderer) {
    //mainMenuEntity->render(renderer);
}

void UIManager::update(const SDL_Event& event) {
    //mainMenuEntity->update(event);
}
