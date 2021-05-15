#include "Game/Entities/GameOverEntity.hpp"
#include "Game/ManagerHelper.hpp"
#include "Engine/Components/TextComponent.hpp"
#include "Engine/Components/InputComponent.hpp"
#include "Engine/Managers/WindowManager.hpp"
#include <iostream>

GameOverEntity::GameOverEntity() {
    SDL_Rect windowSize = ManagerHelper::get<WindowManager>()->getWindowSize();
    setPosition(Eigen::Vector2f(0.413 * windowSize.w, .467 * windowSize.h));
    
    TextComponent* textComponent = new TextComponent("Hyperspace.ttf");
    textComponent->setSize(42);
    textComponent->setText("GAME OVER");
    addComponent(textComponent);
    textComponent->setIsVisible(false);
    
    InputComponent* inputComponent = new InputComponent();
    inputComponent->addBinding(SDLK_RETURN, [this](const SDL_Event& event) -> void {
        if(isGameOver) {
            ManagerHelper::reset();
        }
    });
    
    addComponent(inputComponent);
}

void GameOverEntity::update(const SDL_Event& event) {
    GameEntity::update(event);
    switch(event.type) {
        case SDL_KEYUP: {
            getComponent<InputComponent>()->update(event);
            break;
        }
        case SDL_USEREVENT: {
            switch(event.user.code) {
                case ManagerHelper::EVENT_GAME_OVER: {
                    isGameOver = true;
                    getComponent<TextComponent>()->setIsVisible(true);
                    break;
                }
            }
            break;
        }
    }
}
