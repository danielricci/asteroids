#include "Engine/Components/TextRenderComponent.hpp"
#include "Engine/Managers/UIManager.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Game/Entities/StartMenuEntity.hpp"
#include <iostream>

StartMenuEntity::StartMenuEntity(SDL_Renderer& renderer) : MenuEntity(16, "Start Game") {
    this->addComponent(new TextRenderComponent(this, renderer));
}

void StartMenuEntity::onEntered() {
    std::cout << "StartMenuEntity::onEntered" << std::endl;
}

void StartMenuEntity::onExited() {
    std::cout << "StartMenuEntity::onExited" << std::endl;
}

void StartMenuEntity::onExecute() {
    std::cout << "StartMenuEntity::onExecute" << std::endl;
}
