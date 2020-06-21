#pragma once

#include "Engine/Components/Component.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Entities/Entity.hpp"

#include <SDL.h>

class CollisionComponent : public Component {
public:
    bool isCollidedAABB(const Entity& entity) const {
        TransformComponent* firstTransformComponent = this->getEntity()->getComponent<TransformComponent>();
        TransformComponent* secondTransformComponent = entity.getComponent<TransformComponent>();
        return isCollidedAABBImpl(firstTransformComponent->getRectangle(), secondTransformComponent->getRectangle());
    }
private:
    bool isCollidedAABBImpl(const SDL_Rect& r1, const SDL_Rect& r2) const {
        if(r1.x - (r2.x + r2.w) > 0 || r2.x - (r1.x + r1.w) > 0) {
            return false;
        }
        
        if(r1.y - (r2.y + r2.h) > 0 || r2.y - (r1.y + r1.h) > 0) {
            return false;
        }
        
        return true;
    }
};
