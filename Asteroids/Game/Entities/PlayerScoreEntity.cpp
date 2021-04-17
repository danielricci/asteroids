#include "Engine/Components/FontComponent.hpp"
#include "Game/ManagerHelper.hpp"
#include "Game/Entities/AsteroidEntity.hpp"
#include "Game/Entities/PlayerScoreEntity.hpp"
#include "Game/Entities/SaucerEntity.hpp"

PlayerScoreEntity::PlayerScoreEntity() {
    setPosition(Eigen::Vector2f(310, 50));
    setPrecision(1);
    FontComponent* textComponent = new FontComponent("Hyperspace.ttf");
    textComponent->setSize(32);
    textComponent->setText(toString());
    addComponent(textComponent);
}

void PlayerScoreEntity::update(const SDL_Event& event) {
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
            case ManagerHelper::EVENT_SAUCER_HIT: {
                SaucerEntity* saucerEntity = static_cast<SaucerEntity*>(event.user.data1);
                switch(saucerEntity->saucerType) {
                    case SaucerEntity::SaucerType::SAUCER_SMALL: {
                        addScore(1000);
                        break;
                    }
                    case SaucerEntity::SaucerType::SAUCER_LARGE: {
                        addScore(200);
                        break;
                    }
                }
                break;
            }
        }
    }
}
