#include "Engine/Components/Component.hpp"

void Component::setOwnerEntity(Entity* ownerEntity) {
    this->ownerEntity = ownerEntity;
}
