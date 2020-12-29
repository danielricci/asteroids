#include "Engine/Managers/GameManager.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Engine/Components/PhysicsComponent.hpp"
#include "Engine/Components/RenderComponent.hpp"
#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Game/Entities/AsteroidEntity.hpp"
#include <Eigen/Dense>

AsteroidEntity::AsteroidEntity(AsteroidStage stage) : stage(stage) {
    addComponent(new ShapeComponent(asteroidShapes[static_cast<int>(stage) % static_cast<int>(AsteroidStage::END)]));
    addComponent(new RenderComponent());
    PhysicsComponent* physicsComponent = new PhysicsComponent();
    physicsComponent->eventOnCollide.attach([this](Entity* sender, EventArgs args) {
        if(dynamic_cast<AsteroidEntity*>(sender) == nullptr) {
            auto asteroidStage = static_cast<AsteroidEntity::AsteroidStage>(static_cast<int>(this->stage) + 1);
            AsteroidEntity* a1 = new AsteroidEntity(asteroidStage);
            a1->setPosition(this->getPosition());
            ManagerHelper::get<GameManager>()->addEntity(a1);
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
