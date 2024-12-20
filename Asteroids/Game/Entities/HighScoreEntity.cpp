#include "Engine/Components/TextComponent.hpp"
#include "Engine/Managers/WindowManager.hpp"
#include "Game/Entities/HighScoreEntity.hpp"
#include "Game/Managers/ManagerHelper.hpp"
#include <Eigen/Dense>
#include <SDL.h>

HighScoreEntity::HighScoreEntity() {
    SDL_Rect windowSize = ManagerHelper::get<WindowManager>()->getWindowSize();
    setPosition(Eigen::Vector2f((windowSize.w / 2) - 25, 55));
    
    TextComponent* textComponent = new TextComponent("Hyperspace.ttf");
    textComponent->setSize(24);
    textComponent->setText(toString());
    addComponent(textComponent);
}
