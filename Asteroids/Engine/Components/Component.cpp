#include "Engine/Components/Component.hpp"

bool Component::getIsVisible() const {
    return isVisible;
}

std::string Component::getName() const {
    return this->name;
}

Eigen::Vector2f Component::getPosition() const {
    return position;
}

void Component::render(SDL_Renderer& renderer) {
}

void Component::setIsVisible(bool isVisible) {
    this->isVisible = isVisible;
}

void Component::setName(const std::string& name) {
    this->name = name;
}

void Component::setOwnerEntity(Entity* ownerEntity) {
    this->ownerEntity = ownerEntity;
}

void Component::setPosition(const Eigen::Vector2f& position) {
    this->position = position;
}
