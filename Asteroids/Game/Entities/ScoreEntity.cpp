#include "Engine/Components/TextComponent.hpp"
#include "Game/Entities/ScoreEntity.hpp"

ScoreEntity::ScoreEntity() {
    TextComponent* textComponent = new TextComponent("Hyperspace.ttf");
    textComponent->setText("12345");
    textComponent->setSize(32);
    this->addComponent(textComponent);
    this->setPosition(Eigen::Vector2f(150, 50));
}

void ScoreEntity::render(SDL_Renderer& renderer) {
    getComponent<TextComponent>()->render(renderer);
}
