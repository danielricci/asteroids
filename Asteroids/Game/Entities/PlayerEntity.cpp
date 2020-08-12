#include "Game/Entities/PlayerEntity.hpp"

void PlayerEntity::render(SDL_Renderer& renderer) {
    shape.render(renderer);
}
