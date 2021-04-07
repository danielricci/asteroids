#include "Engine/Components/TextComponent.hpp"
#include "Game/Entities/ScoreEntity.hpp"
#include <iomanip>
#include <sstream>

void ScoreEntity::addScore(int score) {
    this->score = std::min(this->score + score, maxScore);
    getComponent<TextComponent>()->setText(toString());
}

void ScoreEntity::reset() {
    addScore(-score);
}

void ScoreEntity::setMaxScore(int maxScore) {
    this->maxScore = std::max(0, maxScore);
}

void ScoreEntity::setPrecision(int precision) {
    this->precision = std::max(0, precision);
}

std::string ScoreEntity::toString() const {
    std::stringstream ss;
    ss << std::setw(std::max(2, static_cast<int>(std::to_string(score).length()))) << std::setfill('0') << score;
    return ss.str();
}
