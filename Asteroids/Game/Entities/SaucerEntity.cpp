#include "Engine/Components/PhysicsComponent.hpp"
#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Managers/WorldManager.hpp"
#include "Engine/Managers/SoundManager.hpp"
#include "Game/Entities/SaucerEntity.hpp"
#include "Game/Managers/ManagerHelper.hpp"
#include "Game/Particles/EnemyExplosionParticle.hpp"
#include <Eigen/Dense>
#include <SDL.h>

SaucerEntity::SaucerEntity(SaucerType saucerType) : saucerType(saucerType) {
    setPosition(Eigen::Vector2f(0, 200));
    velocity = Eigen::Vector2f(1, 1);
    
    // TODO: Configure the proper waypoints for the saucer
    waypoints.push(Eigen::Vector2f(800, 200));
    waypoints.push(Eigen::Vector2f(600, 500));
    waypoints.push(Eigen::Vector2f(300, 700));
    waypoints.push(Eigen::Vector2f(1280, 700));
    waypoint = waypoints.front();
    
    float scaleFactor = 1.f;
    switch(saucerType) {
        case SaucerType::SAUCER_SMALL: {
            scaleFactor = 0.95;
            break;
        }
        case SaucerType::SAUCER_LARGE: {
            scaleFactor = 1.25;
            break;
        }
    }
    
    addComponent(new ShapeComponent({
        // Top shape
        scaleFactor * Eigen::Vector2f(5, -5),
        scaleFactor * Eigen::Vector2f(10, -12),
        scaleFactor * Eigen::Vector2f(25, -12),
        scaleFactor * Eigen::Vector2f(30, -5),
        scaleFactor * Eigen::Vector2f(5, -5),
        // Middle Shape
        scaleFactor * Eigen::Vector2f(-5, 0),
        scaleFactor * Eigen::Vector2f(40, 0),
        scaleFactor * Eigen::Vector2f(30, -5),
        scaleFactor * Eigen::Vector2f(5, -5),
        scaleFactor * Eigen::Vector2f(-5, 0),
        // Bottom shape
        scaleFactor * Eigen::Vector2f(5, 5),
        scaleFactor * Eigen::Vector2f(30, 5),
        scaleFactor * Eigen::Vector2f(40, 0)
    }));
    
    PhysicsComponent* physicsComponent = new PhysicsComponent();
    physicsComponent->eventOnCollide.attach([this](Entity* sender, EventArgs args) {
        EnemyExplosionParticle* particle = new EnemyExplosionParticle();
        particle->setPosition(this->getPosition());
        particle->setOrientation(this->getOrientation());
        particle->play();
        ManagerHelper::get<WorldManager>()->addEntity(particle);
        
        ManagerHelper::broadcast(ManagerHelper::EVENT_SAUCER_HIT, this, EventArgs::Empty());
        ManagerHelper::get<SoundManager>()->getSound("saucer_explosion")->play();
        ManagerHelper::destroy(this);
    });
    addComponent(physicsComponent);
}

Eigen::AlignedBox2f SaucerEntity::getBounds() const {
    ShapeComponent* shapeComponent = this->getComponent<ShapeComponent>();
    SDL_FRect rectangle = shapeComponent->getRectangle();
    
    Eigen::AlignedBox2f alignedBox;
    alignedBox.min() = this->getPosition() + Eigen::Vector2f(rectangle.x, rectangle.y);
    alignedBox.max() = Eigen::Vector2f(alignedBox.min().x() + rectangle.w, alignedBox.min().y() + rectangle.h);
    return alignedBox;
}

void SaucerEntity::update(float deltaTime) {
    Eigen::Vector2f position = getPosition();
    Eigen::Vector2f distance = waypoint - position;
    if(distance.norm() <= 10) {
        setPosition(waypoint);
        waypoints.pop();
        
        if(waypoints.empty()) {
            ManagerHelper::destroy(this);
        }
        else {
            waypoint = waypoints.front();
        }
    }
    
    Eigen::Vector2f direction = distance/distance.norm();
    position.x() += (direction.x() * speed * deltaTime);
    position.y() += (direction.y() * speed * deltaTime);
    setPosition(position);
}
