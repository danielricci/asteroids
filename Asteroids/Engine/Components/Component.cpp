#include "Engine/Components/Component.hpp"

Component::Component(const std::string& name) : name(name) {
}

void Component::setOwnerEntity(Entity* ownerEntity) {
    this->ownerEntity = ownerEntity;
    if(onOwnerEntityChanged != nullptr) {
        onOwnerEntityChanged();
    }
}
