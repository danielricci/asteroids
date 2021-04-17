#include "Engine/Components/FontComponent.hpp"
#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Managers/GameManager.hpp"
#include "Game/ManagerHelper.hpp"
#include "Game/Entities/LivesEntity.hpp"
#include "Game/Entities/PlayerEntity.hpp"

LivesEntity::LivesEntity() {
    // TODO: Calculate the coordinates with the rotation applied so this doesnt have to be done every frame
    setOrientation(TransformComponent::ROTATION_TOP);
    setPosition(Eigen::Vector2f(310, 90));

    FontComponent* textComponent = new FontComponent("Hyperspace.ttf");
    textComponent->setSize(32);
    addComponent(textComponent);
    
    ShapeComponent* shapeComponent = new ShapeComponent({{12, 0}, {-12, 10}, {-8, 5}, {-8, -5}, {-12, -10}, {12, 0}});
    shapeComponent->setPosition(INITIAL_POSITION_SHAPE);
    addComponent(shapeComponent);
    
    // Note: Must be at the end after all the components have been initialized/added
    addScore(1);
}

void LivesEntity::addScore(int lives) {
    this->lives = std::max(0, std::min(this->lives + lives, MAX_LIVES));
    
    FontComponent* textComponent = getComponent<FontComponent>();
    textComponent->setPosition(OFFSET_POSITION_TEXT * std::to_string(this->lives).length());
    textComponent->setText(toString());
}

void LivesEntity::reset() {
    addScore(-lives);
}

std::string LivesEntity::toString() const {
    return std::to_string(lives);
}

void LivesEntity::render(SDL_Renderer& renderer) {
    if(lives <= PRECISION) {
        ShapeComponent* shapeComponent = getComponent<ShapeComponent>();
        Eigen::Vector2f originalPosition = shapeComponent->getPosition();
        for(int i = 0; i < lives; ++i) {
            Eigen::Vector2f newPosition = originalPosition - (OFFSET_POSITION_SHAPE * (i + 1));
            shapeComponent->setPosition(newPosition);
            shapeComponent->render(renderer);
        }
        shapeComponent->setPosition(originalPosition);
    }
    else {
        getComponent<FontComponent>()->render(renderer);
    }
}

void LivesEntity::update(const SDL_Event& event) {
    if(event.type == SDL_USEREVENT) {
        switch(event.user.code) {
            case ManagerHelper::EVENT_PLAYER_HIT: {
                addScore(-1);
                break;
            }
            case ManagerHelper::EVENT_SPAWN_PLAYER: {
                if(lives > 0) {
                    // TODO: Should be executing from somewhere else, not here
                    ManagerHelper::get<GameManager>()->addEntity(new PlayerEntity());
                }
                else {
                    ManagerHelper::broadcast(ManagerHelper::BroadcastEvent::EVENT_GAME_OVER, this, EventArgs::Empty());
                }
                break;
            }
        }
    }
}
