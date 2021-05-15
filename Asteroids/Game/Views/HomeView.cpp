#include "Engine/Components/TextComponent.hpp"
#include "Engine/Managers/GameManager.hpp"
#include "Engine/Managers/WindowManager.hpp"
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
    
    SDL_Rect windowSize = ManagerHelper::get<WindowManager>()->getWindowSize();
    TextComponent* textComponent = new TextComponent("Hyperspace.ttf", "1 COIN 1 PLAY", 30);
    textComponent->setPosition(Eigen::Vector2f(0.41 * windowSize.w, .80 * windowSize.h));
    this->addComponent(textComponent);
}

void HomeView::update(const SDL_Event& event) {
    switch(event.type) {
        case SDL_KEYUP: {
            if(event.key.keysym.sym == SDLK_RETURN) {
                //TODO: Transition to game view
                break;
            }
        }
    }
}
