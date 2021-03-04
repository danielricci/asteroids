#include "Engine/Components/TextComponent.hpp"
#include "Game/Entities/HighScoreEntity.hpp"
#include <Eigen/Dense>

HighScoreEntity::HighScoreEntity() {
    setPosition(Eigen::Vector2f(450, 250));
    
    TextComponent* textComponent = new TextComponent("Hyperspace.ttf");
    textComponent->setSize(18);
    textComponent->setText(toString());
    addComponent(textComponent);
}
