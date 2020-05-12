#include "Game/Components/SnakeInputComponent.hpp"
#include "Game/Components/TransformComponent.hpp"

SnakeInputComponent::SnakeInputComponent(GameObject* gameObject) : InputComponent(gameObject) {
    this->addBinding(SDLK_UP, ACTION_MOVE, std::bind(&SnakeInputComponent::onMove, this, std::placeholders::_1));
    this->addBinding(SDLK_LEFT, ACTION_MOVE, std::bind(&SnakeInputComponent::onMove, this, std::placeholders::_1));
    this->addBinding(SDLK_DOWN, ACTION_MOVE, std::bind(&SnakeInputComponent::onMove, this, std::placeholders::_1));
    this->addBinding(SDLK_RIGHT, ACTION_MOVE, std::bind(&SnakeInputComponent::onMove, this, std::placeholders::_1));
}

void SnakeInputComponent::onMove(const SDL_Event& event) {
    if(event.type == SDL_KEYDOWN) {
        // Calculate the new velocity w.r.t the input provided
        Eigen::Vector2f newInputVector;
        switch(event.key.keysym.sym) {
            case SDLK_UP: {
                newInputVector.x() = 0;
                newInputVector.y() = -1;
                break;
            }
            case SDLK_LEFT:
                newInputVector.x() = -1;
                newInputVector.y() = 0;
                break;
            case SDLK_DOWN: {
                newInputVector.x() = 0;
                newInputVector.y() = 1;
                break;
            }
            case SDLK_RIGHT: {
                newInputVector.x() = 1;
                newInputVector.y() = 0;
                break;
            }
            default: {
                return;
            }
        }
        
        // Get a reference to the velocity vector of the game object, and ensure that the new desired input is an allowed
        // input w.r.t the direction of the snake.
        Eigen::Vector2f snakeVelocityVector = getGameObject()->getComponent<TransformComponent>()->velocityVector;
        if((newInputVector.x() == 1 || newInputVector.x() == -1) && (snakeVelocityVector.x() == 1 || snakeVelocityVector.x() == -1)) {
            return;
        }
        if((newInputVector.y() == 1 || newInputVector.y() == -1) && (snakeVelocityVector.y() == 1 || snakeVelocityVector.y() == -1)) {
            return;
        }
        inputVector = newInputVector;
    }
}
