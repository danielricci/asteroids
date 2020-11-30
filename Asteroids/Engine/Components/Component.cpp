#include "Engine/Components/Component.hpp"

Component::Component(const std::string& name) : name(name) {
}

void Component::setOwnerEntity(Entity* entityOwner) {
    this->entityOwner = entityOwner;
    if(onOwnerEntityChanged != nullptr) {
        onOwnerEntityChanged();
    }
}
