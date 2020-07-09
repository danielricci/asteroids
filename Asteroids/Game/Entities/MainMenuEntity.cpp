#include "Engine/Components/MenuComponent.hpp"
#include "Engine/Components/TextComponent.hpp"
#include "Engine/Components/TextRenderComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Game/Entities/MainMenuEntity.hpp"
#include <Eigen/Dense>
#include <iostream>


MainMenuEntity::MainMenuEntity() {
    TextComponent* startGame = new TextComponent(24, {0xFF, 0xFF, 0xFF}, "Fonts/Verdana.ttf", "Start Game");
    startGame->setPosition(Eigen::Vector2f(300, 100));
    startGame->addComponent(new TextRenderComponent());
    this->addComponent(startGame);
}

void MainMenuEntity::render(SDL_Renderer& renderer) {
    TextComponent* tc = this->getComponent<TextComponent>();
    tc->getComponent<TextRenderComponent>()->render(renderer);
}

void MainMenuEntity::onEntered() {
    std::cout << "StartMenuEntity::onEntered" << std::endl;
}

void MainMenuEntity::onExited() {
    std::cout << "StartMenuEntity::onExited" << std::endl;
}

void MainMenuEntity::onExecute() {
    std::cout << "StartMenuEntity::onExecute" << std::endl;
}
