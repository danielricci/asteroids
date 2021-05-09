#include "Engine/Managers/GameManager.hpp"
#include "Engine/Managers/ViewManager.hpp"
#include "Game/ManagerHelper.hpp"
#include "Game/Entities/CopyrightEntity.hpp"
#include "Game/Entities/GameOverEntity.hpp"
#include "Game/Entities/HighScoreEntity.hpp"
#include "Game/Entities/LivesEntity.hpp"
#include "Game/Entities/PlayerScoreEntity.hpp"
#include "Game/Views/GameView.hpp"

GameView::GameView() {
    this->isVisible = false;
    
    entities.push_back(new CopyrightEntity());
    entities.push_back(new CopyrightEntity());
    entities.push_back(new GameOverEntity());
    entities.push_back(new HighScoreEntity());
    entities.push_back(new LivesEntity());
    entities.push_back(new PlayerScoreEntity());
}

void GameView::render(SDL_Renderer& renderer) {
    View::render(renderer);
    // TODO: remove the notion of rendering in the game manager
    ((Manager*)ManagerHelper::get<GameManager>())->render(renderer);
}

void GameView::update(const SDL_Event& event) {
    switch(event.type) {
        case SDL_KEYUP: {
            if(event.key.keysym.sym == SDLK_ESCAPE) {
                this->isVisible = false;
                break;
            }
        }
    }
}
