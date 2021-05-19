#include "Engine/Components/TransformComponent.hpp"
#include "Game/Managers/ManagerHelper.hpp"
#include "Game/Particles/EnemyExplosionParticle.hpp"

EnemyExplosionParticle::EnemyExplosionParticle() {
    points.push_back(Eigen::Vector2f(0, 0));
    points.push_back(Eigen::Vector2f(1, 0));
    points.push_back(Eigen::Vector2f(-1, 0));
    points.push_back(Eigen::Vector2f(0, 1));
    points.push_back(Eigen::Vector2f(0, -1));
}

void EnemyExplosionParticle::play() {
    isPlaying = true;
}

void EnemyExplosionParticle::render(SDL_Renderer& renderer) {
    GameEntity::render(renderer);
    if(isPlaying) {
        for(const auto& point : points) {
            Eigen::Vector2f worldPosition = getWorldPosition(point);
            SDL_RenderDrawPoint(&renderer, worldPosition.x(), worldPosition.y());
        }
    }
}

void EnemyExplosionParticle::update(float deltaTime) {
    if(isPlaying) {
        if((elapsedTime += deltaTime) > DURATION) {
            eventOnStop.invoke(this);
            ManagerHelper::destroy(this);
        }
        
        int angle[5];
        angle[0] = 0;
        angle[1] = 30;
        angle[2] = 120;
        angle[3] = 180;
        angle[4] = 300;
                
        for(int i = 0; i < points.size(); ++i) {
            double radians = TransformComponent::toRadians(angle[i]);
            velocity.x() = (SPEED * std::cos(radians));
            velocity.y() = (SPEED * std::sin(radians));
            
            Eigen::Vector2f point = points[i];
            point.x() += (velocity.x() * deltaTime);
            point.y() += (velocity.y() * deltaTime);
            points[i] = point;
        }
    }
}
