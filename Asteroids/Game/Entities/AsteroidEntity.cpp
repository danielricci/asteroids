#include "Engine/Components/RenderComponent.hpp"
#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Game/Entities/AsteroidEntity.hpp"

AsteroidEntity::AsteroidEntity() {
    this->addNode(new RenderComponent());
    ShapeComponent* shapeComponent = new ShapeComponent(asteroidShapes[0]);
    this->addNode(shapeComponent);
    shapeComponent->setPosition({0, 0});
    this->setOrientation(-45);
}

void AsteroidEntity::setAsteroidSize(const AsteroidSize& asteroidSize) {
    switch(asteroidSize) {
        case AsteroidSize::BIG: {
            if(this->asteroidSize != asteroidSize) {
                ShapeComponent* shapeComponent = this->getNode<ShapeComponent>();
                for(int i = 0; i < shapeComponent->getSize(); ++i) {
                    (*shapeComponent)[i].x *= 3;
                    (*shapeComponent)[i].y *= 3;
                }
            }
            break;
        }
        case AsteroidSize::SMALL: {
            if(this->asteroidSize != asteroidSize) {
                ShapeComponent* shapeComponent = this->getNode<ShapeComponent>();
                for(int i = 0; i < shapeComponent->getSize(); ++i) {
                    (*shapeComponent)[i].x /= 3;
                    (*shapeComponent)[i].y /= 3;
                }
            }
            break;
        }
    }
}

void AsteroidEntity::setPosition(const Eigen::Vector2f& position) {
    Entity::setPosition(position);
}

void AsteroidEntity::update(float deltaTime) {
    Eigen::Vector2f velocity = this->getNode<TransformComponent>()->velocity;
    double radians = TransformComponent::toRadians(this->getOrientation());
    velocity.x() = (speed * std::cos(radians));
    velocity.y() = (speed * std::sin(radians));
    
    Eigen::Vector2f position = this->getPosition();
    position.x() += (velocity.x() * deltaTime);
    position.y() += (velocity.y() * deltaTime);
    this->setPosition(position);
}

void AsteroidEntity::render(SDL_Renderer& renderer) {
    for(ShapeComponent* shapeComponent : this->getNodes<ShapeComponent>()) {
        shapeComponent->render(renderer);
    }
}
