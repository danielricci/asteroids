#include "Engine/Components/TextRenderComponent.hpp"
#include "Engine/Entities/TextMenuEntity.hpp"
#include "Game/Entities/MainMenuEntity.hpp"

MainMenuEntity::MainMenuEntity() {
    TextMenuEntity* startGameMenuEntity = new TextMenuEntity("Start Game", 24);
    this->addNode(startGameMenuEntity);

    
    
    //    this->setPosition(Eigen::Vector2f(240, 200));
//
//
//    TextComponent* settings = new TextComponent(24, {0xFF, 0xFF, 0xFF}, "Fonts/Verdana.ttf", "Settings");
//    settings->setPosition(Eigen::Vector2f(0, 50));
//    this->addNode(settings);
//
//    TextComponent* highScores = new TextComponent(24, {0xFF, 0xFF, 0xFF}, "Fonts/Verdana.ttf", "High Scores");
//    highScores->setPosition(Eigen::Vector2f(0, 100));
//    this->addNode(highScores);
//
//    TextComponent* exit = new TextComponent(24, {0xFF, 0xFF, 0xFF}, "Fonts/Verdana.ttf", "Exit");
//    exit->setPosition(Eigen::Vector2f(0, 150));
//    this->addNode(exit);
//
//    this->addNode(new TextRenderComponent());
}

void MainMenuEntity::render(SDL_Renderer& renderer) {
    for(TextMenuEntity* entity : this->getNodes<TextMenuEntity>()) {
        if(entity != nullptr) {
            entity->render(renderer);
        }
    }
}

//
//
//void MainMenuEntity::onEntered() {
//    std::cout << "StartMenuEntity::onEntered" << std::endl;
//}
//
//void MainMenuEntity::onExited() {
//    std::cout << "StartMenuEntity::onExited" << std::endl;
//}
//
//void MainMenuEntity::onExecute() {
//    std::cout << "StartMenuEntity::onExecute" << std::endl;
//}
