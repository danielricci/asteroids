#include "Engine/Components/RenderComponent.hpp"
#include "Engine/Entities/TextMenuControlEntity.hpp"
#include "Engine/Managers/GameManager.hpp"
#include "Engine/Managers/WindowManager.hpp"
#include "Game/Entities/MenuEntity.hpp"
#include "Engine/Managers/ManagerHelper.hpp"

MenuEntity::MenuEntity() {
//    SDL_Rect windowSize = ManagerHelper::get<WindowManager>()->getWindowSize();
//    this->setPosition(Eigen::Vector2f(windowSize.w/2 - 50, windowSize.h/2 - 95));
//
//    TextMenuControlEntity* startGameMenuEntity = new TextMenuControlEntity("Start Game", 24);
//    startGameMenuEntity->onExecute([this]() {
//        ManagerHelper::get<GameManager>()->setGameState(GameManager::GameState::STARTED);
//    });
//    this->addNode(startGameMenuEntity);
//
//    TextMenuControlEntity* settingsMenuEntity = new TextMenuControlEntity("Settings", 24);
//    settingsMenuEntity->setPosition(Eigen::Vector2f(0, 50));
//    settingsMenuEntity->onExecute([]() {
//    });
//    this->addNode(settingsMenuEntity);
//
//    TextMenuControlEntity* highScoresMenuEntity = new TextMenuControlEntity("High Scores", 24);
//    highScoresMenuEntity->setPosition(Eigen::Vector2f(0, 100));
//    highScoresMenuEntity->onExecute([]() {
//    });
//    this->addNode(highScoresMenuEntity);
//
//    TextMenuControlEntity* exitMenuEntity = new TextMenuControlEntity("Exit", 24);
//    exitMenuEntity->setPosition(Eigen::Vector2f(0, 150));
//    exitMenuEntity->onExecute([]() {
//        SDL_Event event;
//        event.type = SDL_QUIT;
//        SDL_PushEvent(&event);
//    });
//    this->addNode(exitMenuEntity);
//    this->addNode(new RenderComponent());
}

void MenuEntity::update(float deltaTime) {
    //this->getNode<RenderComponent>()->isVisible = ManagerHelper::get<GameManager>()->getGameState() != GameManager::GameState::STARTED;
}

void MenuEntity::update(const SDL_Event& event) {
//    if(ManagerHelper::get<GameManager>()->getGameState() != GameManager::GameState::STARTED) {
//        for(TextMenuControlEntity* entity : this->getNodes<TextMenuControlEntity>()) {
//            if(entity != nullptr) {
//                entity->update(event);
//            }
//        }
//    }
}

void MenuEntity::render(SDL_Renderer& renderer) {
//    if(this->getNode<RenderComponent>()->isVisible) {
//        for(TextMenuControlEntity* entity : this->getNodes<TextMenuControlEntity>()) {
//            if(entity != nullptr) {
//                entity->render(renderer);
//            }
//        }
//    }
}
