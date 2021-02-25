#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TextComponent.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Game/Entities/LivesEntity.hpp"
#include "Game/Entities/PlayerEntity.hpp"

LivesEntity::LivesEntity() {
    setPosition(Eigen::Vector2f(230, 80));

    TextComponent* textComponent = new TextComponent("Hyperspace.ttf");
    textComponent->setSize(32);
    textComponent->setText(toString());
    addComponent(textComponent);
    
    ShapeComponent* shapeComponent = new ShapeComponent({{0, 0}, {10, 24}, {0, 20}, {-10, 24}, {0, 0}});
    shapeComponent->setPosition(Eigen::Vector2f(28, 8));
    addComponent(shapeComponent);
}

void LivesEntity::addLives(int lives) {
    this->lives = std::max(0, std::min(this->lives + lives, MAX_LIVES));
    getComponent<TextComponent>()->setText(toString());
}

void LivesEntity::render(SDL_Renderer& renderer) {
    lives > 3 ? getComponent<TextComponent>()->render(renderer) : getComponent<ShapeComponent>()->render(renderer);
}

void LivesEntity::reset() {
    addLives(-lives);
}

std::string LivesEntity::toString() const {
    return std::to_string(lives);
}

void LivesEntity::update(const SDL_Event& event) {
    if(event.type == SDL_USEREVENT) {
        switch(event.user.code) {
            case ManagerHelper::EVENT_PLAYER_DEATH: {
                addLives(-1);
                break;
            }
        }
    }
}
