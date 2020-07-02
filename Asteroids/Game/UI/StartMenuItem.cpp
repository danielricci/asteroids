#include "Engine/Components/TextRenderComponent.hpp"
#include "Engine/Managers/UIManager.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Game/UI/StartMenuItem.hpp"
#include <iostream>

StartMenuItem::StartMenuItem() : MenuItem(16, "Start Game") {
    this->addComponent(new TextRenderComponent(this, ManagerHelper::get<UIManager>()->getRenderer()));
}

void StartMenuItem::onEntered() {
    std::cout << "StartMenu::onEntered" << std::endl;
}

void StartMenuItem::onExited() {
    std::cout << "StartMenu::onExited" << std::endl;
}

void StartMenuItem::onExecute() {
    std::cout << "StartMenu::onExecute" << std::endl;
}
