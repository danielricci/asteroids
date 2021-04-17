#include "Engine/Components/FontComponent.hpp"
#include "Engine/Managers/WindowManager.hpp"
#include "Game/ManagerHelper.hpp"
#include "Game/Entities/HighScoreEntity.hpp"
#include <Eigen/Dense>
#include <SDL.h>

HighScoreEntity::HighScoreEntity() {
    SDL_Rect windowSize = ManagerHelper::get<WindowManager>()->getWindowSize();
    setPosition(Eigen::Vector2f((windowSize.w / 2) - 25, 55));
    
    FontComponent* textComponent = new FontComponent("Hyperspace.ttf");
    textComponent->setSize(24);
    textComponent->setText(toString());
    addComponent(textComponent);
}
