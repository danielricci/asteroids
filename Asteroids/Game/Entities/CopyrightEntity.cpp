#include "Engine/Components/TextComponent.hpp"
#include "Engine/Managers/WindowManager.hpp"
#include "Game/ManagerHelper.hpp"
#include "Game/Entities/CopyrightEntity.hpp"
#include <Eigen/Dense>
#include <SDL.h>

CopyrightEntity::CopyrightEntity() {
    SDL_Rect windowSize = ManagerHelper::get<WindowManager>()->getWindowSize();
    setPosition(Eigen::Vector2f(0.42 * windowSize.w, .90 * windowSize.h));
    
    TextComponent* textComponent = new TextComponent("Hyperspace.ttf");
    textComponent->setSize(20);
    textComponent->setText("(C) 1979 ATARI INC");
    addComponent(textComponent);
}
