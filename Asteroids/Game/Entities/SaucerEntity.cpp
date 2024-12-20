#include "Engine/Components/PhysicsComponent.hpp"
#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Managers/SoundManager.hpp"
#include "Engine/Managers/WorldManager.hpp"
#include "Game/Entities/BulletEntity.hpp"
#include "Game/Entities/PlayerEntity.hpp"
#include "Game/Entities/SaucerEntity.hpp"
#include "Game/Managers/ManagerHelper.hpp"
#include "Game/Particles/EnemyExplosionParticle.hpp"
#include <Eigen/Dense>
#include <SDL.h>

SaucerEntity::SaucerEntity(SaucerType saucerType) : saucerType(saucerType) {
    setPosition(Eigen::Vector2f(0, 400));
    velocity = Eigen::Vector2f(1, 1);
    
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
        BulletEntity* bulletEntity = dynamic_cast<BulletEntity*>(sender);
        if(bulletEntity != nullptr && !bulletEntity->fromPlayer) {
            return;
        }
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
    
    // Note: Harcoded waypoints for the time being
    waypoints.push(Eigen::Vector2f(1280, 400));
    waypoint = waypoints.front();
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
    GameEntity::update(deltaTime);
    
    Eigen::Vector2f saucerPosition = getPosition();
    Eigen::Vector2f distance = waypoint - saucerPosition;
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
    saucerPosition.x() += (direction.x() * speed * deltaTime);
    saucerPosition.y() += (direction.y() * speed * deltaTime);
    setPosition(saucerPosition);
    
    timerBullet += deltaTime;
    if(timerBullet >= .5) {
        timerBullet = 0;
        
        PlayerEntity* playerEntity = ManagerHelper::get<WorldManager>()->get<PlayerEntity>();
        if(playerEntity != nullptr) {
            Eigen::Vector2f directionVector = playerEntity->getPosition() - saucerPosition;
            
            BulletEntity* bulletEntity = new BulletEntity(this);
            bulletEntity->setOrientation(TransformComponent::toDegrees(std::atan(directionVector.y() / directionVector.x())));
            bulletEntity->setPosition(getPosition());
            
            ManagerHelper::get<WorldManager>()->addEntity(bulletEntity);
        }
    }
}
