#include "Engine/Managers/GameManager.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Engine/Components/PhysicsComponent.hpp"
#include "Engine/Components/RenderComponent.hpp"
#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Game/Entities/SaucerEntity.hpp"
#include <Eigen/Dense>
#include <iostream>
#include <list>

SaucerEntity::SaucerEntity(SaucerLevel level) : level(level) {
    std::list<ShapeComponent*> shapeComponents;
    switch(level) {
        case SaucerLevel::LEVEL_1: {
            shapeComponents.push_back(new ShapeComponent());
            break;
        }
        case SaucerLevel::LEVEL_MAX: {
            break;
        }
        default: {
            std::cerr << "Could not determine the saucer level" << std::endl;
        }
    }
//    switch(stage) {
//        case AsteroidStage::STAGE_1: {
//            shapeComponent  = new ShapeComponent(asteroidShapes[0]);
//            break;
//        }
//        case AsteroidStage::STAGE_LAST: {
//            shapeComponent  = new ShapeComponent(asteroidShapes[asteroidShapes.size() - 1]);
//            break;
//        }
//        default: {
//            std::cerr << "Could not determine the asteroid stage" << std::endl;
//            break;
//        }
//    }
//    speed *= static_cast<int>(stage) + 1;
//    addComponent(shapeComponent);
    
    PhysicsComponent* physicsComponent = new PhysicsComponent();
    physicsComponent->eventOnCollide.attach([this](Entity* sender, EventArgs args) {
        ManagerHelper::clean(this);
    });
    addComponent(physicsComponent);
}

SDL_Rect SaucerEntity::getEntityBounds() const {
    return {0,0,0,0};
//    SDL_Rect bounds = getComponent<ShapeComponent>()->getShapeBounds();
//    Eigen::Vector2f position = getPosition();
//    bounds.x += position.x();
//    bounds.y += position.y();
//    return bounds;
}

void SaucerEntity::update(float deltaTime) {
    Eigen::Vector2f velocity = getComponent<TransformComponent>()->velocity;
    double radians = TransformComponent::toRadians(getOrientation());
    velocity.x() = (speed * std::cos(radians));
    velocity.y() = (speed * std::sin(radians));

    Eigen::Vector2f position = getPosition();
    position.x() += (velocity.x() * deltaTime);
    position.y() += (velocity.y() * deltaTime);
    setPosition(position);
}

void SaucerEntity::update(const SDL_Event& event) {
}

void SaucerEntity::render(SDL_Renderer& renderer) {
    getComponent<PhysicsComponent>()->render(renderer);
    //getComponent<ShapeComponent>()->render(renderer);
}
