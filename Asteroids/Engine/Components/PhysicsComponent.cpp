#include "Engine/Components/PhysicsComponent.hpp"
#include "Engine/Entities/Entity.hpp"
#include "SDL2_gfxPrimitives.h"


bool PhysicsComponent::collide(const Entity& entity) const {
    SDL_Rect r1 = this->ownerEntity->getDimensionVector();
    SDL_Rect r2 = entity.getDimensionVector();
    
    if(r1.x - (r2.x + r2.w) > 0 || r2.x - (r1.x + r1.w) > 0) {
        return false;
    }

    if(r1.y - (r2.y + r2.h) > 0 || r2.y - (r1.y + r1.h) > 0) {
        return false;
    }

    return true;
}

void PhysicsComponent::render(SDL_Renderer& renderer) {
    if(getIsVisible()) {
        SDL_Color color;
        SDL_GetRenderDrawColor(&renderer, &color.r, &color.g, &color.b, &color.a);
        SDL_SetRenderDrawColor(&renderer, 0xFF, 0x00, 0x00, SDL_ALPHA_OPAQUE);
        SDL_Rect rect = this->ownerEntity->getDimensionVector();
        SDL_RenderDrawRect(&renderer, &rect);
        SDL_SetRenderDrawColor(&renderer, color.r, color.g, color.b, color.a);
    }
}
