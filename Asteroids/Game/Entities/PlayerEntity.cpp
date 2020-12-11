#include "Engine/Components/CollisionComponent.hpp"
#include "Engine/Components/RenderComponent.hpp"
#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/SoundComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Managers/GameManager.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Engine/Managers/WindowManager.hpp"
#include "Game/Components/PlayerInputComponent.hpp"
#include "Game/Entities/BulletEntity.hpp"
#include "Game/Entities/PlayerEntity.hpp"
#include <cmath>
#include <random>

PlayerEntity::PlayerEntity() {
    // Orient the player facing upwards
    getComponent<TransformComponent>()->orientation = TransformComponent::ORIENTATION_NORTH;

    // Create the player input controls and set up the bindings
    PlayerInputComponent* playerInputComponent = new PlayerInputComponent();
    playerInputComponent->registerActionBinding(PlayerInputComponent::EVENT_SHOOT, std::bind(&PlayerEntity::onEventShoot, this, std::placeholders::_1));
    playerInputComponent->registerActionBinding(PlayerInputComponent::EVENT_HYPERSPACE, std::bind(&PlayerEntity::onEventHyperspace, this, std::placeholders::_1));
    addComponent(playerInputComponent);

    // Create the player ship
    ShapeComponent* playerShapeComponent = new ShapeComponent({{0, 0}, {-24, 10}, {-20, 0}, {-24, -10}, {0, 0}});
    playerShapeComponent->name = PLAYER_SHAPE;
    addComponent(playerShapeComponent);
    // Translate the player ships' shape positions so that the
    // world position of the entity has its origin at the center (avoids having to do any origin normalization for each rotational tick)
    SDL_Point shapeCenterPoint = playerShapeComponent->getShapeCenter();
    for(int i = 0; i < playerShapeComponent->getSize(); ++i) {
        (*playerShapeComponent)[i].x += shapeCenterPoint.x;
    }
    
    // Create the shape for when the player is moving
    ShapeComponent* playerThrust = new ShapeComponent({{-9, -3}, {-20, 0}, {-9, 3}});
    playerThrust->name = PLAYER_THRUST_SHAPE;
    this->addComponent(playerThrust);

    // Create the sound components associated to the player entity
//    SoundComponent* thrustSoundComponent = new SoundComponent("Thrust.wav");
//    thrustSoundComponent->name = THRUST_SOUND;
//    this->addComponent(thrustSoundComponent);

//    CollisionComponent* collisionComponent = new CollisionComponent();
//    this->addComponent(collisionComponent);
}

void PlayerEntity::render(SDL_Renderer& renderer) {
    //PlayerInputComponent* playerInputComponent = this->getComponent<PlayerInputComponent>();
    //RenderComponent* thrustRenderComponent = this->getComponent<ShapeComponent>(PLAYER_THRUST_SHAPE)->get<RenderComponent>();
    //thrustRenderComponent->isVisible = playerInputComponent->getMovementAction() == PlayerInputComponent::PlayerAction::THRUST;
    for(ShapeComponent* shapeComponent : this->getComponents<ShapeComponent>()) {
        shapeComponent->render(renderer);
    }
}

void PlayerEntity::update(const SDL_Event& event) {
    switch(event.type) {
        case SDL_KEYDOWN:
        case SDL_KEYUP: {
            PlayerInputComponent* playerInputComponent = this->getComponent<PlayerInputComponent>();
            if(playerInputComponent != nullptr) {
                playerInputComponent->update(event);
            }
            break;
        }
    }
}

void PlayerEntity::update(float deltaTime) {
    PlayerInputComponent* playerInputComponent = getComponent<PlayerInputComponent>();
    if(playerInputComponent != nullptr) {
        // Compute the orientation
        TransformComponent* playerTransform = getComponent<TransformComponent>();
        switch(playerInputComponent->getRotationAction()) {
            case PlayerInputComponent::PlayerAction::ROTATE_LEFT: {
                playerTransform->orientation = (static_cast<int>(playerTransform->orientation - (deltaTime * 360)) % 360);
                break;
            }
            case PlayerInputComponent::PlayerAction::ROTATE_RIGHT: {
                playerTransform->orientation = (static_cast<int>(playerTransform->orientation + (deltaTime * 360)) % 360);
                break;
            }
            default: {
                break;
            }
        }
        // Compute the position
        switch(playerInputComponent->getMovementAction()) {
            case PlayerInputComponent::PlayerAction::THRUST: {
                double radians = TransformComponent::toRadians(playerTransform->orientation);
                Eigen::Vector2f velocity = playerTransform->velocity;
                velocity.x() += (std::cos(radians) * acceleration);
                velocity.y() += (std::sin(radians) * acceleration);
                velocity.x() = std::clamp(velocity.x(), -maxSpeed, maxSpeed);
                velocity.y() = std::clamp(velocity.y(), -maxSpeed, maxSpeed);
                playerTransform->velocity = velocity;
                break;
            }
            default: {
                break;
            }
        }
        // Set the position
        Eigen::Vector2f position = this->getPosition();
        position.x() += (playerTransform->velocity.x() * deltaTime);
        position.y() += (playerTransform->velocity.y() * deltaTime);
        this->setPosition(position);
    }
}

void PlayerEntity::onEventHyperspace(const SDL_Event& event) {
    switch(event.type) {
        case SDL_KEYUP: {
            PlayerInputComponent* playerInputComponent = getComponent<PlayerInputComponent>();
            playerInputComponent->reset();

            TransformComponent* transformComponent = getComponent<TransformComponent>();
            transformComponent->velocity = {0, 0};

            SDL_Rect windowSize = ManagerHelper::get<WindowManager>()->getWindowSize();

            std::uniform_int_distribution<unsigned int> widthDistribution(0, windowSize.w);
            std::uniform_int_distribution<unsigned int> heightDistribution(0, windowSize.h);
            std::mt19937 generator(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
            setPosition({widthDistribution(generator), heightDistribution(generator)});
        }
    }
}

void PlayerEntity::onEventShoot(const SDL_Event& event) {
    switch(event.type) {
        case SDL_KEYUP: {
            BulletEntity* bulletEntity = new BulletEntity();
            bulletEntity->getComponent<TransformComponent>()->velocity = this->getComponent<TransformComponent>()->velocity;
            bulletEntity->setOrientation(getOrientation());

            ShapeComponent* playerShapeComponent = getComponent<ShapeComponent>();
            SDL_Point finalPosition = playerShapeComponent->getVertexPosition((*playerShapeComponent)[0]);
            bulletEntity->setPosition({finalPosition.x, finalPosition.y});
            ManagerHelper::get<GameManager>()->addEntity(bulletEntity);

            break;
        }
    }
}
