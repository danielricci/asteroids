#include "Engine/Components/MenuComponent.hpp"
#include "Engine/Components/TextComponent.hpp"
#include "Engine/Components/TextRenderComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Game/Entities/MainMenuEntity.hpp"
#include <Eigen/Dense>
#include <iostream>
#include <list>

MainMenuEntity::MainMenuEntity() {
//    TextComponent* startGame = new TextComponent(24, {0xFF, 0x00, 0x00}, "Fonts/Verdana.ttf", "Start Game");
//    this->addComponent(startGame);
//    
//    TextComponent* settings = new TextComponent(24, {0x00, 0xFF, 0x00}, "Fonts/Verdana.ttf", "Settings");
//    this->addComponent(settings);
//    
//    TextComponent* highScores = new TextComponent(24, {0x00, 0x00, 0xFF}, "Fonts/Verdana.ttf", "High Scores");
//    this->addComponent(highScores);
//    
//    TextComponent* exitGame = new TextComponent(24, {0xFF, 0x00, 0xFF}, "Fonts/Verdana.ttf", "Exit Game");
//    this->addComponent(exitGame);
}

void MainMenuEntity::render(SDL_Renderer& renderer) {
    //std::list<TextComponent*> textComponents = this->getAll<TextComponent>();
//    for(TextComponent* textComponent : textComponents) {
//
//    }
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
