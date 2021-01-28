#include "Engine/Components/PhysicsComponent.hpp"
#include "Engine/Entities/Entity.hpp"
#include <SDL.h>

bool PhysicsComponent::isCollidedWith(const Entity& entity) const {
//    Eigen::Vector2f thisPosition = this->ownerEntity->getPosition();
//    Eigen::Vector2f thisDimensions = this->ownerEntity->getDimensions();
//
//
//
//
//
//
//
//
//
//    Eigen::Vector2f thatPosition = entity.getPosition();
//    Eigen::Vector2f thatDimensions = entity.getDimensions();
//
    return false;
//    SDL_Rect r1;
//    SDL_Rect r2;
//    SDL_HasIntersection(<#const SDL_Rect *A#>, <#const SDL_Rect *B#>)
//

    
    
    
//    SDL_Rect r1 = this->ownerEntity->getEntityBounds();
//    SDL_Rect r2 = entity.getEntityBounds();
//
//    if(r1.x - (r2.x + r2.w) > 0 || r2.x - (r1.x + r1.w) > 0) {
//        return false;
//    }
//
//    if(r1.y - (r2.y + r2.h) > 0 || r2.y - (r1.y + r1.h) > 0) {
//        return false;
//    }
}

void PhysicsComponent::render(SDL_Renderer& renderer) {
    Eigen::Vector2f thisPosition = this->ownerEntity->getPosition();
    Eigen::Vector2f thisDimensions = this->ownerEntity->getDimensions();
    
    SDL_Rect rect;
    rect.x = thisPosition.x();
    rect.y = thisPosition.y();
    rect.w = thisDimensions.x();
    rect.h = thisDimensions.y();
    
    SDL_Color color;
    SDL_GetRenderDrawColor(&renderer, &color.r, &color.g, &color.b, &color.a);
    SDL_SetRenderDrawColor(&renderer, 0x00, 0xFF, 0x00, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(&renderer, &rect);
    SDL_SetRenderDrawColor(&renderer, color.r, color.g, color.b, color.a);
}
