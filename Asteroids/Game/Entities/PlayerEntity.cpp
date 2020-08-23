#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Game/Entities/PlayerEntity.hpp"
#include "Game/Components/PlayerInputComponent.hpp"
#include <Eigen/Dense>

PlayerEntity::PlayerEntity() {
    this->addNode(new ShapeComponent{{0, 0}, {9, 24}, {0, 20}, {-9, 24}, {0, 0}});
    this->addNode(new PlayerInputComponent());
}

void PlayerEntity::render(SDL_Renderer& renderer) {
    this->getNode<ShapeComponent>()->render(renderer);
}

void PlayerEntity::update(const SDL_Event& event) {
    switch(event.type) {
        case SDL_KEYDOWN:
        case SDL_KEYUP: {
            PlayerInputComponent* playerInputComponent = this->getNode<PlayerInputComponent>();
            if(playerInputComponent != nullptr) {
                playerInputComponent->update(event);
            }
            break;
        }
    }
}

void PlayerEntity::update(float deltaTime) {
    PlayerInputComponent* playerInputComponent = this->getNode<PlayerInputComponent>();
    if(playerInputComponent != nullptr) {
        switch(playerInputComponent->getPlayerAction()) {
            case PlayerInputComponent::PlayerAction::NONE: {
                break;
            }
            case PlayerInputComponent::PlayerAction::ROTATE_LEFT: {
                
                break;
            }
            case PlayerInputComponent::PlayerAction::ROTATE_RIGHT: {
                
                break;
            }
        }
    }
}
