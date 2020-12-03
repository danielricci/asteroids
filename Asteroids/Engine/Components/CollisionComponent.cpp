#include "Engine/Components/CollisionComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include <SDL.h>

CollisionComponent::CollisionComponent() {
    //this->addNode(new TransformComponent());
}

bool CollisionComponent::isValidCollision() {
    return false;
}

bool CollisionComponent::isCollidedAABB(const Entity& entity) const {
    return false;
//    TransformComponent* firstTransformComponent = this->getEntity()->getComponent<TransformComponent>();
//    TransformComponent* secondTransformComponent = entity.getComponent<TransformComponent>();
//    return isCollidedAABBImpl(firstTransformComponent->getRectangle(), secondTransformComponent->getRectangle());
//
//    if(r1.x - (r2.x + r2.w) > 0 || r2.x - (r1.x + r1.w) > 0) {
//        return false;
//    }
//
//    if(r1.y - (r2.y + r2.h) > 0 || r2.y - (r1.y + r1.h) > 0) {
//        return false;
//    }
//
//    return true;
}
