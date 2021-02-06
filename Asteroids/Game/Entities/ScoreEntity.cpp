#include "Engine/Components/TextComponent.hpp"
#include "Game/Entities/ScoreEntity.hpp"
#include <string>

ScoreEntity::ScoreEntity() {
    TextComponent* textComponent = new TextComponent("Hyperspace.ttf");
    textComponent->setSize(32);
    this->addComponent(textComponent);
    this->setPosition(Eigen::Vector2f(150, 50));
    this->addScore(score);
}

void ScoreEntity::reset() {
    this->score = 0;
    getComponent<TextComponent>()->setText(std::to_string(score));
}

void ScoreEntity::addScore(int score) {
    this->score += score;
    getComponent<TextComponent>()->setText(std::to_string(score));
}

void ScoreEntity::render(SDL_Renderer& renderer) {
    getComponent<TextComponent>()->render(renderer);
}
