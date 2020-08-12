#include "Engine/Components/ShapeComponent.hpp"
#include "Game/Entities/PlayerEntity.hpp"

PlayerEntity::PlayerEntity() {
    this->addNode(new ShapeComponent{{0, 0}, {9, 24}, {0, 20}, {-9, 24}, {0, 0}});
}

void PlayerEntity::render(SDL_Renderer& renderer) {
    this->getNode<ShapeComponent>()->render(renderer);
}
