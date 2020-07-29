#include "Engine/Entities/TextMenuControlEntity.hpp"
#include "Game/Entities/MainMenuEntity.hpp"
#include <iostream>

MainMenuEntity::MainMenuEntity() {
    TextMenuControlEntity* startGameMenuEntity = new TextMenuControlEntity("Start Game", 24);
    startGameMenuEntity->setPosition(Eigen::Vector2f(0, 0));
    startGameMenuEntity->onExecute([]() {
        std::cout << "Start Game" << std::endl;
    });
    this->addNode(startGameMenuEntity);

    TextMenuControlEntity* settingsMenuEntity = new TextMenuControlEntity("Settings", 24);
    settingsMenuEntity->setPosition(Eigen::Vector2f(0, 50));
    settingsMenuEntity->onExecute([]() {
        std::cout << "Settings" << std::endl;
    });
    this->addNode(settingsMenuEntity);

    TextMenuControlEntity* highScoresMenuEntity = new TextMenuControlEntity("High Scores", 24);
    highScoresMenuEntity->setPosition(Eigen::Vector2f(0, 100));
    highScoresMenuEntity->onExecute([]() {
        std::cout << "High Scores" << std::endl;
    });
    this->addNode(highScoresMenuEntity);

    TextMenuControlEntity* exitMenuEntity = new TextMenuControlEntity("Exit", 24);
    exitMenuEntity->setPosition(Eigen::Vector2f(0, 150));
    exitMenuEntity->onExecute([]() {
        SDL_Event event;
        event.type = SDL_QUIT;
        SDL_PushEvent(&event);
    });
    this->addNode(exitMenuEntity);
    this->setPosition(Eigen::Vector2f(220, 175));
}

void MainMenuEntity::update(const SDL_Event& event) {
    for(TextMenuControlEntity* entity : this->getNodes<TextMenuControlEntity>()) {
        if(entity != nullptr) {
            entity->update(event);
        }
    }
}

void MainMenuEntity::render(SDL_Renderer& renderer) {
    for(TextMenuControlEntity* entity : this->getNodes<TextMenuControlEntity>()) {
        if(entity != nullptr) {
            entity->render(renderer);
        }
    }
}
