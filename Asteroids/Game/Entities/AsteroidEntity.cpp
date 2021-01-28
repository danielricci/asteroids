#include "Engine/Components/PhysicsComponent.hpp"
#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Managers/GameManager.hpp"
#include "Game/Entities/AsteroidEntity.hpp"
#include "Game/Managers/ManagerHelper.hpp"
#include <Eigen/Dense>

AsteroidEntity::AsteroidEntity(AsteroidStage stage) : stage(stage) {
    ShapeComponent* shapeComponent = nullptr;
    switch(stage) {
        case AsteroidStage::STAGE_1: {
            shapeComponent  = new ShapeComponent({{-20, -50}, {20, -40}, {30, -20}, {40, 10}, {20, 15}, {35, 35}, {30, 50}, {0, 35}, {-25, 50}, {-40, 10}, {-40, -10}, {-23.5, -20}, {-20, -50}});
            break;
        }
        case AsteroidStage::STAGE_2: {
            //shapeComponent = new ShapeComponent({{0, 0}, {20, 0}, {40, 20}, {40, 30}, {20, 40}, {40, 50}, {30, 60}, {20, 50}, {0, 60}, {-10, 40}, {-10, 20}, {10, 20}, {0, 0}});
            shapeComponent  = new ShapeComponent({{-20, -50}, {20, -40}, {30, -20}, {40, 10}, {20, 15}, {35, 35}, {30, 50}, {0, 35}, {-25, 50}, {-40, 10}, {-40, -10}, {-23.5, -20}, {-20, -50}});
            break;
        }
        case AsteroidStage::STAGE_LAST: {
            //shapeComponent  = new ShapeComponent({{0, 0}, {10, 0}, {20, 10}, {20, 15}, {10, 20}, {20, 25}, {15, 30}, {10, 25}, {0, 30}, {-5, 20}, {-5, 10}, {5, 10}, {0, 0}});
            shapeComponent  = new ShapeComponent({{-20, -50}, {20, -40}, {30, -20}, {40, 10}, {20, 15}, {35, 35}, {30, 50}, {0, 35}, {-25, 50}, {-40, 10}, {-40, -10}, {-23.5, -20}, {-20, -50}});
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
                    asteroid->setOrientation(TransformComponent::getRandomRotation());
                    ManagerHelper::get<GameManager>()->addEntity(asteroid);
                }
            }
            ManagerHelper::clean(this);
        }
    });
    addComponent(physicsComponent);
}

void AsteroidEntity::render(SDL_Renderer& renderer) {
    getComponent<ShapeComponent>()->render(renderer);
    getComponent<PhysicsComponent>()->render(renderer);
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

void AsteroidEntity::update(const SDL_Event& event) {
}
