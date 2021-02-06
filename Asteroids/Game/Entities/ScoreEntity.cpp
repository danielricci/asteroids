#include "Engine/Components/TextComponent.hpp"
#include "Game/Entities/ScoreEntity.hpp"

ScoreEntity::ScoreEntity() {
    TextComponent* textComponent = new TextComponent("Hyperspace.ttf");
    textComponent->setText("12345");
    textComponent->setSize(24);
    this->addComponent(textComponent);
}

void ScoreEntity::render(SDL_Renderer& renderer) {
    getComponent<TextComponent>()->render(renderer);
}
