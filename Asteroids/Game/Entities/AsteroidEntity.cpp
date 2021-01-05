#include "Engine/Components/PhysicsComponent.hpp"
#include "Engine/Components/RenderComponent.hpp"
#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Managers/GameManager.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Game/Entities/AsteroidEntity.hpp"
#include <Eigen/Dense>
#include <iostream>

AsteroidEntity::AsteroidEntity(AsteroidStage stage) : stage(stage) {
    ShapeComponent* shapeComponent = nullptr;
    switch(stage) {
        case AsteroidStage::STAGE_1: {
            shapeComponent  = new ShapeComponent(asteroidShapes[0]);
            break;
        }
        case AsteroidStage::STAGE_2: {
            shapeComponent = new ShapeComponent(asteroidShapes[1]);
            break;
        }
        case AsteroidStage::STAGE_LAST: {
            shapeComponent  = new ShapeComponent(asteroidShapes[asteroidShapes.size() - 1]);
            break;
        }
        default: {
            std::cerr << "Could not determine the asteroid stage" << std::endl;
            break;
        }
    }
    addComponent(shapeComponent);
    
    speed *= static_cast<int>(stage) + 1;
    
    PhysicsComponent* physicsComponent = new PhysicsComponent();
    physicsComponent->eventOnCollide.attach([this](Entity* sender, EventArgs args) {
        if(dynamic_cast<AsteroidEntity*>(sender) == nullptr) {
            if(this->stage != AsteroidStage::STAGE_LAST) {
                for(int i = 0; i < 3; ++i) {
                    AsteroidEntity* asteroid = new AsteroidEntity(static_cast<AsteroidStage>(static_cast<int>(this->stage) + 1));
                    asteroid->setPosition(this->getPosition());
                    asteroid->setOrientation(TransformComponent::getRandomOrientation());
                    ManagerHelper::get<GameManager>()->addEntity(asteroid);
                }
            }
            ManagerHelper::clean(this);
        }
    });
    addComponent(physicsComponent);
}

SDL_Rect AsteroidEntity::getEntityBounds() const {
    SDL_Rect bounds = getComponent<ShapeComponent>()->getShapeBounds();
    Eigen::Vector2f position = getPosition();
    bounds.x += position.x();
    bounds.y += position.y();
    return bounds;
}

void AsteroidEntity::update(float deltaTime) {
    Eigen::Vector2f velocity = getComponent<TransformComponent>()->velocity;
    double radians = TransformComponent::toRadians(getOrientation());
    velocity.x() = (speed * std::cos(radians));
    velocity.y() = (speed * std::sin(radians));

    Eigen::Vector2f position = getPosition();
    position.x() += (velocity.x() * deltaTime);
    position.y() += (velocity.y() * deltaTime);
    setPosition(position);
}

void AsteroidEntity::update(const SDL_Event& event) {
}

void AsteroidEntity::render(SDL_Renderer& renderer) {
    getComponent<PhysicsComponent>()->render(renderer);
    getComponent<ShapeComponent>()->render(renderer);
}
