#include "Engine/Components/PhysicsComponent.hpp"
#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Managers/GameManager.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Engine/System/EventArgs.hpp"
#include "Game/Entities/AsteroidEntity.hpp"
#include <SDL.h>

AsteroidEntity::AsteroidEntity(AsteroidStage stage) : stage(stage) {
    
    int stageNumeral = static_cast<int>(stage);
    float stageSizeScalar = 1.f / stageNumeral;
    addComponent(new ShapeComponent({
        stageSizeScalar * Eigen::Vector2f(-20, -50),
        stageSizeScalar * Eigen::Vector2f(20, -40),
        stageSizeScalar * Eigen::Vector2f(30, -20),
        stageSizeScalar * Eigen::Vector2f(40, 10),
        stageSizeScalar * Eigen::Vector2f(20, 15),
        stageSizeScalar * Eigen::Vector2f(35, 35),
        stageSizeScalar * Eigen::Vector2f(30, 50),
        stageSizeScalar * Eigen::Vector2f(0, 35),
        stageSizeScalar * Eigen::Vector2f(-25, 50),
        stageSizeScalar * Eigen::Vector2f(-40, 10),
        stageSizeScalar * Eigen::Vector2f(-40, -10),
        stageSizeScalar * Eigen::Vector2f(-23.5, -20),
        stageSizeScalar * Eigen::Vector2f(-20, -50)
    }));
    
    speed *= stageNumeral + 1;
    
    PhysicsComponent* physicsComponent = new PhysicsComponent();
    physicsComponent->eventOnCollide.attach([this, stageNumeral](Entity* sender, EventArgs args) {
        if(dynamic_cast<AsteroidEntity*>(sender) == nullptr) {
            ManagerHelper::broadcast(ManagerHelper::EVENT_ASTEROID_HIT, this, EventArgs());
            if(this->stage != AsteroidStage::STAGE_LAST) {
                for(int i = 0, j = stageNumeral * 2; i < j; ++i) {
                    AsteroidEntity* asteroid = new AsteroidEntity(static_cast<AsteroidStage>(stageNumeral + 1));
                    asteroid->setPosition(this->getPosition());
                    asteroid->setOrientation(TransformComponent::getRandomRotation());
                    ManagerHelper::get<GameManager>()->addEntity(asteroid);
                }
            }
            ManagerHelper::clean(this);
        }
    });
    addComponent(physicsComponent);
}

Eigen::AlignedBox2f AsteroidEntity::getBounds() const {
    ShapeComponent* shapeComponent = this->getComponent<ShapeComponent>();
    SDL_FRect rectangle = shapeComponent->getRectangle();
    
    Eigen::AlignedBox2f alignedBox;
    alignedBox.min() = this->getPosition() + Eigen::Vector2f(rectangle.x, rectangle.y);
    alignedBox.max() = Eigen::Vector2f(alignedBox.min().x() + rectangle.w, alignedBox.min().y() + rectangle.h);
    return alignedBox;
}

void AsteroidEntity::update(float deltaTime) {
    double radians = TransformComponent::toRadians(getOrientation());
    velocity.x() = (speed * std::cos(radians));
    velocity.y() = (speed * std::sin(radians));

    Eigen::Vector2f position = getPosition();
    position.x() += (velocity.x() * deltaTime);
    position.y() += (velocity.y() * deltaTime);
    setPosition(position);
}
