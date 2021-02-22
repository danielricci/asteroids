#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TextComponent.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Game/Entities/AsteroidEntity.hpp"
#include "Game/Entities/ScoreEntity.hpp"
#include <iomanip>
#include <sstream>

ScoreEntity::ScoreEntity() {
    TextComponent* textComponent = new TextComponent("Hyperspace.ttf");
    textComponent->setPosition(Eigen::Vector2f(150, 50));
    textComponent->setSize(32);
    textComponent->setText(toString());
    this->addComponent(textComponent);    
//    for(int i = 0; i < 3; ++i) {
//        ShapeComponent* shapeComponent = new ShapeComponent({{12, 0}, {-12, 10}, {-8, 0}, {-12, -10}, {12, 0}});
//        shapeComponent->setPosition(Eigen::Vector2f(300, 300));
//        addComponent(shapeComponent);
//    }
}

//void ScoreEntity::addLives(int lives) {
//    this->lives += lives;
//    getComponent<TextComponent>()->setText(toString());
//}

void ScoreEntity::addScore(int score) {
    this->score = std::min(this->score + score, MAX_SCORE);
    getComponent<TextComponent>()->setText(toString());
}

void ScoreEntity::render(SDL_Renderer& renderer) {
    getComponent<TextComponent>()->render(renderer);
}

void ScoreEntity::reset() {
    addScore(-score);
}

void ScoreEntity::update(const SDL_Event& event) {
    if(event.type == SDL_USEREVENT) {
        switch(event.user.code) {
            case ManagerHelper::EVENT_ASTEROID_HIT: {
                AsteroidEntity* asteroidEntity = static_cast<AsteroidEntity*>(event.user.data1);
                switch(asteroidEntity->stage) {
                    case AsteroidEntity::AsteroidStage::STAGE_1: {
                        addScore(50);
                        break;
                    }
                    case AsteroidEntity::AsteroidStage::STAGE_2: {
                        addScore(75);
                        break;
                    }
                    case AsteroidEntity::AsteroidStage::STAGE_LAST: {
                        addScore(125);
                        break;
                    }
                }
                break;
            }
        }
    }
}

std::string ScoreEntity::toString() const {
    std::stringstream ss;
    ss << std::setw(PRECISION) << std::setfill('0') << score;
    return ss.str();
}
