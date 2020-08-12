#include "Engine/Components/RenderComponent.hpp"
#include "Engine/Entities/TextMenuControlEntity.hpp"
#include "Engine/Managers/GameManager.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Engine/Managers/SettingsManager.hpp"
#include "Game/Entities/MainMenuEntity.hpp"

MainMenuEntity::MainMenuEntity() {
    int width = 0;
    int height = 0;
    ManagerHelper::get<SettingsManager>()->getWindowSize(width, height);
    this->setPosition(Eigen::Vector2f(width/2, height/2));
    
    TextMenuControlEntity* startGameMenuEntity = new TextMenuControlEntity("Start Game", 24);
    startGameMenuEntity->onExecute([this]() {
        ManagerHelper::get<GameManager>()->setGameState(GameManager::GameState::STARTED);
    });
    this->addNode(startGameMenuEntity);

    TextMenuControlEntity* settingsMenuEntity = new TextMenuControlEntity("Settings", 24);
    settingsMenuEntity->setPosition(Eigen::Vector2f(0, 50));
    settingsMenuEntity->onExecute([]() {
    });
    this->addNode(settingsMenuEntity);

    TextMenuControlEntity* highScoresMenuEntity = new TextMenuControlEntity("High Scores", 24);
    highScoresMenuEntity->setPosition(Eigen::Vector2f(0, 100));
    highScoresMenuEntity->onExecute([]() {
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
    this->addNode(new RenderComponent());
}

void MainMenuEntity::update(float deltaTime) {
    this->getNode<RenderComponent>()->isVisible = ManagerHelper::get<GameManager>()->getGameState() != GameManager::GameState::STARTED;
}

void MainMenuEntity::update(const SDL_Event& event) {
    if(ManagerHelper::get<GameManager>()->getGameState() != GameManager::GameState::STARTED) {
        for(TextMenuControlEntity* entity : this->getNodes<TextMenuControlEntity>()) {
            if(entity != nullptr) {
                entity->update(event);
            }
        }
    }
}

void MainMenuEntity::render(SDL_Renderer& renderer) {
    if(this->getNode<RenderComponent>()->isVisible) {
        for(TextMenuControlEntity* entity : this->getNodes<TextMenuControlEntity>()) {
            if(entity != nullptr) {
                entity->render(renderer);
            }
        }
    }
}
