#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TextComponent.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Game/Entities/LivesEntity.hpp"
#include "Game/Entities/PlayerEntity.hpp"

LivesEntity::LivesEntity() {
    setPosition(Eigen::Vector2f(310, 80));

    TextComponent* textComponent = new TextComponent("Hyperspace.ttf");
    textComponent->setSize(32);
    addComponent(textComponent);
    
    ShapeComponent* shapeComponent = new ShapeComponent({{0, 0}, {10, 24}, {0, 20}, {-10, 24}, {0, 0}});
    shapeComponent->setPosition(INITIAL_POSITION_SHAPE);
    addComponent(shapeComponent);
    
    // Note: Must be at the end after all the components have been initialized/added
    addScore(3);
}

void LivesEntity::addScore(int lives) {
    this->lives = std::max(0, std::min(this->lives + lives, MAX_LIVES));
    
    TextComponent* textComponent = getComponent<TextComponent>();
    textComponent->setPosition(OFFSET_POSITION_TEXT * std::to_string(this->lives).length());
    textComponent->setText(toString());
}

void LivesEntity::reset() {
    addScore(-lives);
}

std::string LivesEntity::toString() const {
    return std::to_string(lives);
}

void LivesEntity::render(SDL_Renderer& renderer) {
    if(lives <= PRECISION) {
        ShapeComponent* shapeComponent = getComponent<ShapeComponent>();
        Eigen::Vector2f originalPosition = shapeComponent->getPosition();
        for(int i = 0; i < lives; ++i) {
            Eigen::Vector2f newPosition = originalPosition - (OFFSET_POSITION_SHAPE * (i + 1));
            shapeComponent->setPosition(newPosition);
            shapeComponent->render(renderer);
        }
        shapeComponent->setPosition(originalPosition);
    }
    else {
        getComponent<TextComponent>()->render(renderer);
    }
    
}

void LivesEntity::update(const SDL_Event& event) {
    if(event.type == SDL_USEREVENT) {
        switch(event.user.code) {
            case ManagerHelper::EVENT_PLAYER_DEATH: {
                addScore(-1);
                break;
            }
        }
    }
}
