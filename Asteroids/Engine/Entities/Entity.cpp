#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Entities/Entity.hpp"
#include "Engine/Managers/WindowManager.hpp"
#include "Engine/Managers/ManagerHelper.hpp"

Entity::Entity() {
    this->addNode(new TransformComponent());
}

void Entity::update(float deltaTime) {
}

void Entity::update(const SDL_Event& event) {
}

void Entity::render(SDL_Renderer& renderer) {
}

void Entity::setPosition(const Eigen::Vector2f& position) {
    SDL_Rect windowSize = ManagerHelper::get<WindowManager>()->getWindowSize();
    
    Eigen::Vector2f normalizedPosition = position;
    if(normalizedPosition.x() < 0) {
        normalizedPosition.x() += windowSize.w;
    }
    else if(normalizedPosition.x() > windowSize.w) {
        normalizedPosition.x() -= windowSize.w;
    }
    
    if(normalizedPosition.y() < 0) {
        normalizedPosition.y() += windowSize.h;
    }
    else if(normalizedPosition.y() > windowSize.h) {
        normalizedPosition.y() -= windowSize.h;
    }
    
    Node::setPosition(normalizedPosition);
}
