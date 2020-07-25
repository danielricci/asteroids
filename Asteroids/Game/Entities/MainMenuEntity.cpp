#include "Engine/Components/TextRenderComponent.hpp"
#include "Engine/Entities/TextMenuEntity.hpp"
#include "Game/Entities/MainMenuEntity.hpp"
#include <iostream>

MainMenuEntity::MainMenuEntity() {
    TextMenuEntity* startGameMenuEntity = new TextMenuEntity("Start Game", 24);
    startGameMenuEntity->setPosition(Eigen::Vector2f(0, 0));
    startGameMenuEntity->onExecute([]() {
        std::cout << "Start Game" << std::endl;
    });
    this->addNode(startGameMenuEntity);

    TextMenuEntity* settingsMenuEntity = new TextMenuEntity("Settings", 24);
    settingsMenuEntity->setPosition(Eigen::Vector2f(0, 50));
    settingsMenuEntity->onExecute([]() {
        std::cout << "Settings" << std::endl;
    });
    this->addNode(settingsMenuEntity);

    TextMenuEntity* highScoresMenuEntity = new TextMenuEntity("High Scores", 24);
    highScoresMenuEntity->setPosition(Eigen::Vector2f(0, 100));
    highScoresMenuEntity->onExecute([]() {
        std::cout << "High Scores" << std::endl;
    });
    this->addNode(highScoresMenuEntity);

    TextMenuEntity* exitMenuEntity = new TextMenuEntity("Exit", 24);
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
    for(TextMenuEntity* entity : this->getNodes<TextMenuEntity>()) {
        if(entity != nullptr) {
            entity->update(event);
        }
    }
}

void MainMenuEntity::render(SDL_Renderer& renderer) {
    for(TextMenuEntity* entity : this->getNodes<TextMenuEntity>()) {
        if(entity != nullptr) {
            entity->render(renderer);
        }
    }
}
