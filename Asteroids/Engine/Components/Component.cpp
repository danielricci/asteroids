#include "Engine/Components/Component.hpp"
#include "Engine/Components/RenderComponent.hpp"

Component::~Component() {
    if(renderComponent != nullptr) {
        delete renderComponent;
        renderComponent = nullptr;
    }
}

RenderComponent* Component::getRenderComponent() {
    if(renderComponent == nullptr) {
        renderComponent = new RenderComponent();
    }
    return renderComponent;
}

void Component::render(SDL_Renderer& renderer) {
}

void Component::setOwnerEntity(Entity* ownerEntity) {
    this->ownerEntity = ownerEntity;
}

void Component::setIsVisible(bool isVisible) {
    getRenderComponent()->isVisible = isVisible;
}

bool Component::getIsVisible() {
    return getRenderComponent()->isVisible;
}
