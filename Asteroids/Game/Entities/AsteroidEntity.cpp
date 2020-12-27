#include "Engine/Components/PhysicsComponent.hpp"
#include "Engine/Components/RenderComponent.hpp"
#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Game/Entities/AsteroidEntity.hpp"
#include <Eigen/Dense>

AsteroidEntity::AsteroidEntity() {
    addComponent(new ShapeComponent(asteroidShapes[0]));
    addComponent(new RenderComponent());
    addComponent(new PhysicsComponent());
    setPosition({300, 300});
}

//void AsteroidEntity::setAsteroidSize(const AsteroidSize& asteroidSize) {
//    switch(asteroidSize) {
//        case AsteroidSize::BIG: {
//            if(this->asteroidSize != asteroidSize) {
//                ShapeComponent* shapeComponent = this->getNode<ShapeComponent>();
//                for(int i = 0; i < shapeComponent->getSize(); ++i) {
//                    (*shapeComponent)[i].x *= 3;
//                    (*shapeComponent)[i].y *= 3;
//                }
//            }
//            break;
//        }
//        case AsteroidSize::SMALL: {
//            if(this->asteroidSize != asteroidSize) {
//                ShapeComponent* shapeComponent = this->getNode<ShapeComponent>();
//                for(int i = 0; i < shapeComponent->getSize(); ++i) {
//                    (*shapeComponent)[i].x /= 3;
//                    (*shapeComponent)[i].y /= 3;
//                }
//            }
//            break;
//        }
//    }
//}

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
    getComponent<ShapeComponent>()->render(renderer);    
    getComponent<PhysicsComponent>()->render(renderer);
}
