#include "Engine/Components/TextComponent.hpp"
#include "Engine/Managers/ViewManager.hpp"
#include "Engine/Managers/WindowManager.hpp"
#include "Engine/Managers/WorldManager.hpp"
#include "Game/Entities/GameOverEntity.hpp"
#include "Game/Entities/HighScoreEntity.hpp"
#include "Game/Entities/LivesEntity.hpp"
#include "Game/Entities/PlayerEntity.hpp"
#include "Game/Entities/PlayerScoreEntity.hpp"
#include "Game/Managers/ManagerHelper.hpp"
#include "Game/Managers/StageManager.hpp"
#include "Game/Views/GameView.hpp"
#include <Eigen/Dense>

GameView::GameView() {
    
    GameOverEntity* gameOverEntity = new GameOverEntity();
    gameOverEntity->eventOnConfirmation.attach([this](Entity* sender, EventArgs args) {
        HighScoreEntity* highScoreEntity = getEntity<HighScoreEntity>(true);
        int currentScore = getEntity<PlayerScoreEntity>()->getScore();
        if(currentScore > highScoreEntity->getScore()) {
            highScoreEntity->setScore(currentScore);
        }
                                                       
        ManagerHelper::get<ViewManager>()->setActiveView("home_view");
    });
    
    entities.push_back(gameOverEntity);
    entities.push_back(new LivesEntity());
    entities.push_back(new PlayerScoreEntity(Eigen::Vector2f(210, 50)));
    SDL_Rect windowSize = ManagerHelper::get<WindowManager>()->getWindowSize();
    TextComponent* gamePausedTextComponent = new TextComponent("Hyperspace.ttf", "GAME PAUSED", 42);
    gamePausedTextComponent->setPosition(Eigen::Vector2f(.39 * windowSize.w, .47 * windowSize.h));
    gamePausedTextComponent->setVisible(false);
    addComponent(gamePausedTextComponent);
}


std::string GameView::getViewName() const {
    return "game_view";
}

void GameView::onViewActivated() {
    getEntity<LivesEntity>()->reset();
    getEntity<PlayerScoreEntity>()->reset();
    ManagerHelper::get<StageManager>()->reset();
    ManagerHelper::get<WorldManager>()->addEntity(new PlayerEntity());
}

void GameView::render(SDL_Renderer& renderer) {
    View::render(renderer);
    ((Manager*)ManagerHelper::get<WorldManager>())->render(renderer);
}

void GameView::update(const SDL_Event& event) {
    View::update(event);
    switch(event.type) {
        case SDL_KEYUP: {
            if(event.key.keysym.sym == SDLK_ESCAPE) {
                WorldManager* worldManager = ManagerHelper::get<WorldManager>();
                switch(worldManager->getWorldState()) {
                    case WorldManager::WorldState::RUNNING: {
                        worldManager->setGameState(WorldManager::WorldState::PAUSED);
                        this->getComponent<TextComponent>()->setVisible(true);
                        break;
                    }
                    case WorldManager::WorldState::PAUSED: {
                        worldManager->setGameState(WorldManager::WorldState::RUNNING);
                        this->getComponent<TextComponent>()->setVisible(false);
                        break;
                    }
                    case WorldManager::WorldState::STOPPED:
                    default: {
                        break;
                    }
                }
                break;
            }
        }
    }
}
