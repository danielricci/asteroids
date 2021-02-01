#include "Engine/Components/PhysicsComponent.hpp"
#include "Engine/Entities/Entity.hpp"
#include <SDL.h>

bool PhysicsComponent::isCollidedWith(const Entity& entity) const {
    return false;
}

void PhysicsComponent::render(SDL_Renderer& renderer) {
    Eigen::AlignedBox2f bounds = this->ownerEntity->getBounds();

    SDL_Rect rect;
    rect.x = bounds.min().x();
    rect.y = bounds.min().y();
    rect.w = bounds.max().x() - rect.x;
    rect.h = bounds.max().y() - rect.y;

    SDL_Color color;
    SDL_GetRenderDrawColor(&renderer, &color.r, &color.g, &color.b, &color.a);
    SDL_SetRenderDrawColor(&renderer, 0x00, 0xFF, 0x00, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawPointF(&renderer, bounds.min().x(), bounds.min().y());
    SDL_RenderDrawPointF(&renderer, bounds.max().x(), bounds.max().y());
    //SDL_RenderDrawRect(&renderer, &rect);
    SDL_SetRenderDrawColor(&renderer, color.r, color.g, color.b, color.a);
}
