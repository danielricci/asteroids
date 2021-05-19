#include "Engine/Components/TextComponent.hpp"
#include "Engine/Managers/GameManager.hpp"
#include "Engine/Managers/ViewManager.hpp"
#include "Engine/Managers/WindowManager.hpp"
#include "Game/Entities/CopyrightEntity.hpp"
#include "Game/Entities/GameOverEntity.hpp"
#include "Game/Entities/HighScoreEntity.hpp"
#include "Game/Entities/PlayerScoreEntity.hpp"
#include "Game/Managers/ManagerHelper.hpp"
#include "Game/Views/HomeView.hpp"

HomeView::HomeView() {
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

std::string HomeView::getViewName() const {
    return "home_view";
}

void HomeView::update(const SDL_Event& event) {
    switch(event.type) {
        case SDL_KEYUP: {
            if(event.key.keysym.sym == SDLK_RETURN) {
                ManagerHelper::get<ViewManager>()->setActiveView("game_view");
                break;
            }
        }
    }
}
