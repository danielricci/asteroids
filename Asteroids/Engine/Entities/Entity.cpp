#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Entities/Entity.hpp"
#include "Engine/Managers/GameSettingsManager.hpp"
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
    int width = 0;
    int height = 0;
    ManagerHelper::get<GameSettingsManager>()->getWindowSize(width, height);
    
    Eigen::Vector2f normalizedPosition = position;
    if(normalizedPosition.x() < 0) {
        normalizedPosition.x() = width;
    }
    else if(normalizedPosition.x() > width) {
        normalizedPosition.x() = 0;
    }
    
    if(normalizedPosition.y() < 0) {
        normalizedPosition.y() = height;
    }
    else if(normalizedPosition.y() > height) {
        normalizedPosition.y() = 0;
    }
    
    Node::setPosition(normalizedPosition);
}
