#include "Engine/Components/MenuComponent.hpp"
#include "Engine/Components/TextComponent.hpp"
#include "Engine/Components/TextRenderComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Game/Entities/MainMenuEntity.hpp"
#include <Eigen/Dense>
#include <iostream>
#include <list>

MainMenuEntity::MainMenuEntity() {
    this->addComponent(new TextComponent(24, {0xFF, 0x00, 0x00}, "Fonts/Verdana.ttf", "Start Game"));
    this->addComponent(new TextComponent(24, {0x00, 0xFF, 0x00}, "Fonts/Verdana.ttf", "Settings"));
    this->addComponent(new TextComponent(24, {0x00, 0x00, 0xFF}, "Fonts/Verdana.ttf", "High Scores"));
    this->addComponent(new TextComponent(24, {0xFF, 0x00, 0xFF}, "Fonts/Verdana.ttf", "Exit Game"));
    this->addComponent(new TextRenderComponent());
}

void MainMenuEntity::render(SDL_Renderer& renderer) {
    TextRenderComponent* textRenderComponent = this->getComponent<TextRenderComponent>();
    for(TextComponent* textComponent : this->getAllComponents<TextComponent>()) {
        if(textComponent != nullptr) {
            textRenderComponent->render(renderer, *textComponent);
        }
    }
}

void MainMenuEntity::onEntered() {
    std::cout << "StartMenuEntity::onEntered" << std::endl;
}

void MainMenuEntity::onExited() {
    std::cout << "StartMenuEntity::onExited" << std::endl;
}

void MainMenuEntity::onExecute() {
    std::cout << "StartMenuEntity::onExecute" << std::endl;
}
