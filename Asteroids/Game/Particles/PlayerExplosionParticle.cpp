#include "Engine/Components/TransformComponent.hpp"
#include "Game/Entities/PlayerEntity.hpp"
#include "Game/ManagerHelper.hpp"
#include "Game/Particles/PlayerExplosionParticle.hpp"

PlayerExplosionParticle::PlayerExplosionParticle() {
    edges.push_back(std::pair<Eigen::Vector2f, Eigen::Vector2f>({{6, -4}, {2, 4}}));
    edges.push_back(std::pair<Eigen::Vector2f, Eigen::Vector2f>({{2, 0}, {-6, 8}}));
    edges.push_back(std::pair<Eigen::Vector2f, Eigen::Vector2f>({{0, -1}, {-7, 6}}));
    edges.push_back(std::pair<Eigen::Vector2f, Eigen::Vector2f>({{-2, -2}, {0, 4}}));
    edges.push_back(std::pair<Eigen::Vector2f, Eigen::Vector2f>({{-9, -5}, {9, 0}}));
}

void PlayerExplosionParticle::render(SDL_Renderer& renderer) {
    GameEntity::render(renderer);
    if(isPlaying) {
        for(const auto& edge : edges) {
            Eigen::Vector2f position1 = getWorldPosition(edge.first);
            Eigen::Vector2f position2 = getWorldPosition(edge.second);
            SDL_RenderDrawLineF(&renderer, position1.x(), position1.y(), position2.x(), position2.y());
        }
    }
}

void PlayerExplosionParticle::update(float deltaTime) {
    if(isPlaying) {
        if((elapsedTime += deltaTime) > DURATION) {
            eventOnStop.invoke(this);
            ManagerHelper::clean(this);
        }
        
        int angle[5];
        angle[0] = 0;
        angle[1] = 30;
        angle[2] = 120;
        angle[3] = 180;
        angle[4] = 300;
                
        for(int i = 0; i < edges.size(); ++i) {
            double radians = TransformComponent::toRadians(angle[i]);
            velocity.x() = (SPEED * std::cos(radians));
            velocity.y() = (SPEED * std::sin(radians));
            
            Eigen::Vector2f edge1 = edges[i].first;
            edge1.x() += (velocity.x() * deltaTime);
            edge1.y() += (velocity.y() * deltaTime);
            edges[i].first = edge1;
            
            Eigen::Vector2f edge2 = edges[i].second;
            edge2.x() += (velocity.x() * deltaTime);
            edge2.y() += (velocity.y() * deltaTime);
            edges[i].second = edge2;
        }
    }
}

void PlayerExplosionParticle::update(const SDL_Event& event) {
    if(event.type == SDL_USEREVENT) {
        switch(event.user.code) {
            case ManagerHelper::EVENT_PLAYER_HIT: {
                PlayerEntity* playerEntity = static_cast<PlayerEntity*>(event.user.data1);
                setPosition(playerEntity->getPosition());
                setOrientation(playerEntity->getOrientation());
                isPlaying = true;
                break;
            }
        }
    }
}
