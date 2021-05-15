#include "Engine/Managers/GameManager.hpp"
#include "Game/ManagerHelper.hpp"
#include "Game/Entities/CopyrightEntity.hpp"
#include "Game/Entities/GameOverEntity.hpp"
#include "Game/Entities/HighScoreEntity.hpp"
#include "Game/Entities/LivesEntity.hpp"
#include "Game/Entities/PlayerScoreEntity.hpp"
#include "Game/Views/HomeView.hpp"

HomeView::HomeView() {
    this->isVisible = true;
    
    entities.push_back(new CopyrightEntity());
    entities.push_back(new GameOverEntity());
    entities.push_back(new HighScoreEntity());
    entities.push_back(new PlayerScoreEntity(Eigen::Vector2f(210, 50)));
    entities.push_back(new PlayerScoreEntity(Eigen::Vector2f(1010, 50)));
}

void HomeView::update(const SDL_Event& event) {
    switch(event.type) {
        case SDL_KEYUP: {
            if(event.key.keysym.sym == SDLK_RETURN) {
                break;
            }
        }
    }
}
