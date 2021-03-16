#include "Engine/Components/TextComponent.hpp"
#include "Game/ManagerHelper.hpp"
#include "Engine/Managers/WindowManager.hpp"
#include "Game/Entities/HighScoreEntity.hpp"
#include <Eigen/Dense>
#include <SDL.h>

HighScoreEntity::HighScoreEntity() {
    setPrecision(2);
    
    SDL_Rect windowSize = ManagerHelper::get<WindowManager>()->getWindowSize();
    setPosition(Eigen::Vector2f((windowSize.w / 2) - 25, 55));
    
    TextComponent* textComponent = new TextComponent("Hyperspace.ttf");
    textComponent->setSize(24);
    textComponent->setText(toString());
    addComponent(textComponent);
}
