#include "Engine/Components/TextComponent.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Game/Entities/LivesEntity.hpp"
#include "Game/Entities/PlayerEntity.hpp"

LivesEntity::LivesEntity() {
    TextComponent* textComponent = new TextComponent("Hyperspace.ttf");
    textComponent->setPosition(Eigen::Vector2f(250, 80));
    textComponent->setSize(32);
    textComponent->setText("2");
    addComponent(textComponent);
       
    //    for(int i = 0; i < 3; ++i) {
    //        ShapeComponent* shapeComponent = new ShapeComponent({{12, 0}, {-12, 10}, {-8, 0}, {-12, -10}, {12, 0}});
    //        shapeComponent->setPosition(Eigen::Vector2f(300, 300));
    //        addComponent(shapeComponent);
    //    }
}

void LivesEntity::decrement() {
    --lives;
}

void LivesEntity::increment() {
    ++lives;
}

void LivesEntity::render(SDL_Renderer& renderer) {
    GameEntity::render(renderer);
}

void LivesEntity::reset() {
    lives = 0;
}

void LivesEntity::update(const SDL_Event& event) {
    if(event.type == SDL_USEREVENT) {
        switch(event.user.code) {
            case ManagerHelper::EVENT_PLAYER_DEATH: {
                
                break;
            }
        }
    }
}
