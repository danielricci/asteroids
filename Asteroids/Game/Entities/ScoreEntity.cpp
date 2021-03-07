#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TextComponent.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Game/Entities/AsteroidEntity.hpp"
#include "Game/Entities/ScoreEntity.hpp"
#include <Eigen/Dense>
#include <iomanip>
#include <sstream>

void ScoreEntity::addScore(int score) {
    this->score = std::min(this->score + score, MAX_SCORE);
    getComponent<TextComponent>()->setText(toString());
}

void ScoreEntity::reset() {
    addScore(-score);
}

std::string ScoreEntity::toString() const {
    std::stringstream ss;
    ss << std::setw(PRECISION) << std::setfill('0') << score;
    return ss.str();
}
