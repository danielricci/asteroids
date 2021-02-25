#include "Engine/Components/Component.hpp"
#include "Engine/Components/RenderComponent.hpp"

Component::~Component() {
    if(renderComponent != nullptr) {
        delete renderComponent;
        renderComponent = nullptr;
    }
}

bool Component::getIsVisible() const {
    return getRenderComponent()->isVisible;
}

std::string Component::getName() const {
    return this->name;
}

RenderComponent* Component::getRenderComponent() const {
    return renderComponent;
}

void Component::render(SDL_Renderer& renderer) {
}

void Component::setIsVisible(bool isVisible) {
    getRenderComponent()->isVisible = isVisible;
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

Eigen::Vector2f Component::getPosition() const {
    return position;
}
