#include "Engine/Components/TextComponent.hpp"
#include "Game/Entities/ScoreEntity.hpp"
#include <iomanip>
#include <sstream>

ScoreEntity::ScoreEntity() {
    TextComponent* textComponent = new TextComponent("Hyperspace.ttf");
    textComponent->setSize(32);
    this->addComponent(textComponent);
    this->setPosition(Eigen::Vector2f(150, 50));
    this->addScore(12);
}

void ScoreEntity::reset() {
    this->score = 0;
    getComponent<TextComponent>()->setText(toString());
}

void ScoreEntity::addScore(int score) {
    this->score += score;
    getComponent<TextComponent>()->setText(toString());
}

std::string ScoreEntity::toString() const {
    std::stringstream ss;
    ss << std::setw(precision) << std::setfill('0') << score;
    return ss.str();
}
void ScoreEntity::render(SDL_Renderer& renderer) {
    getComponent<TextComponent>()->render(renderer);
}
