#include "Engine/Components/TextComponent.hpp"
#include "Engine/Managers/ViewManager.hpp"
#include "Engine/Managers/WindowManager.hpp"
#include "Engine/Managers/WorldManager.hpp"
#include "Game/Entities/CopyrightEntity.hpp"
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
    entities.push_back(new CopyrightEntity());
    entities.push_back(new GameOverEntity());
    entities.push_back(new HighScoreEntity());
    entities.push_back(new LivesEntity());
    entities.push_back(new PlayerScoreEntity(Eigen::Vector2f(210, 50)));
    SDL_Rect windowSize = ManagerHelper::get<WindowManager>()->getWindowSize();
    TextComponent* textComponent = new TextComponent("Hyperspace.ttf", "GAME PAUSED", 42);
    textComponent->setIsVisible(false);
    textComponent->setPosition(Eigen::Vector2f(.37 * windowSize.w, .47 * windowSize.h));
    this->addComponent(textComponent);
}


std::string GameView::getViewName() const {
    return "game_view";
}

void GameView::onViewActivated() {
    ManagerHelper::get<StageManager>()->reset();
    ManagerHelper::get<WorldManager>()->addEntity(new PlayerEntity());
}

void GameView::render(SDL_Renderer& renderer) {
    View::render(renderer);
    // TODO: remove the notion of rendering in the game manager
    ((Manager*)ManagerHelper::get<WorldManager>())->render(renderer);
}

void GameView::update(const SDL_Event& event) {
    switch(event.type) {
        case SDL_KEYUP: {
            if(event.key.keysym.sym == SDLK_ESCAPE) {
                WorldManager* worldManager = ManagerHelper::get<WorldManager>();
                switch(worldManager->getWorldState()) {
                    case WorldManager::WorldState::RUNNING: {
                        worldManager->setGameState(WorldManager::WorldState::PAUSED);
                        this->getComponent<TextComponent>()->setIsVisible(true);
                        break;
                    }
                    case WorldManager::WorldState::PAUSED: {
                        worldManager->setGameState(WorldManager::WorldState::RUNNING);
                        this->getComponent<TextComponent>()->setIsVisible(false);
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
