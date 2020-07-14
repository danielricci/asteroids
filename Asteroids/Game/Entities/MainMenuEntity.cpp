#include "Engine/Components/MenuComponent.hpp"
#include "Engine/Components/TextComponent.hpp"
#include "Engine/Components/TextRenderComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Game/Entities/MainMenuEntity.hpp"
#include <Eigen/Dense>
#include <iostream>
#include <list>

MainMenuEntity::MainMenuEntity() {
    this->setPosition(100, 100);
    
    TextComponent* startGame = new TextComponent(24, {0xFF, 0xFF, 0xFF}, "Fonts/Verdana.ttf", "Start Game");
    startGame->setPosition({3, 5});
    this->addNode(startGame);
    
//    TextComponent* settings = new TextComponent(24, {0xFF, 0xFF, 0x00}, "Fonts/Verdana.ttf", "Settings");
//    this->addNode(settings);
//
//    TextComponent* highScores = new TextComponent(24, {0xFF, 0x00, 0xFF}, "Fonts/Verdana.ttf", "High Scores");
//    this->addNode(highScores);
//
//    TextComponent* exit = new TextComponent(24, {0xFF, 0x0F, 0x0F}, "Fonts/Verdana.ttf", "Exit");
//    this->addNode(exit);
        
    this->addNode(new TextRenderComponent());
}

void MainMenuEntity::render(SDL_Renderer& renderer) {
    TextRenderComponent* textRenderComponent = this->getNode<TextRenderComponent>();
    for(TextComponent* textComponent : this->getNodes<TextComponent>()) {
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
