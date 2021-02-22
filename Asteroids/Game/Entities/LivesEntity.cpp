#include "Engine/Components/TextComponent.hpp"
#include "Game/Entities/LivesEntity.hpp"

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
