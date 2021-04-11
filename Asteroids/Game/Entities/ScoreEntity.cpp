#include "Engine/Components/TextComponent.hpp"
#include "Game/Entities/ScoreEntity.hpp"
#include <iomanip>
#include <sstream>

void ScoreEntity::addScore(int score) {
    int oldScore = this->score;
    this->score = std::min(oldScore + score, maxScore);
    
    int count = static_cast<int>(std::to_string(this->score).length() - std::to_string(oldScore).length());
    if(count > 0) {
        this->setPosition(this->getPosition() + (count * OFFSET_POSITION_TEXT));
    }
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
    ss << std::setw(std::max(precision, static_cast<int>(std::to_string(score).length()))) << std::setfill('0') << score;
    return ss.str();
}
