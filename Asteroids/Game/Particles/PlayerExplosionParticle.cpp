#include "Engine/Components/ShapeComponent.hpp"
#include "Game/Particles/PlayerExplosionParticle.hpp"
#include "Game/ManagerHelper.hpp"

PlayerExplosionParticle::PlayerExplosionParticle(PlayerEntity* playerEntity) {
    this->playerEntity = playerEntity;
    ShapeComponent* playerShape = this->playerEntity->getComponent<ShapeComponent>(PlayerEntity::PLAYER_SHIP);
    if(playerShape != nullptr) {
        for(int i = 0; i < playerShape->getSize() - 1; ++i) {
            edges.push_back(std::pair<Eigen::Vector2f, Eigen::Vector2f>((*playerShape)[i], (*playerShape)[i + 1]));
        }
    }
}

void PlayerExplosionParticle::play() {
    if(!isPlaying) {
        setPosition(playerEntity->getPosition());
        setOrientation(playerEntity->getOrientation());
        isPlaying = true;
    }
}

void PlayerExplosionParticle::render(SDL_Renderer& renderer) {
    if(isPlaying) {
        for(const auto& edge : edges) {
            Eigen::Vector2f position1 = getPosition(edge.first);
            Eigen::Vector2f position2 = getPosition(edge.second);
            SDL_RenderDrawLineF(&renderer, position1.x(), position1.y(), position2.x(), position2.y());
        }
    }
}

void PlayerExplosionParticle::update(float deltaTime) {
    if(isPlaying) {
        
    }
}

void PlayerExplosionParticle::update(const SDL_Event& event) {
    if(event.type == SDL_USEREVENT) {
        switch(event.user.code) {
            case ManagerHelper::EVENT_PLAYER_HIT: {
                play();
                break;
            }
        }
    }
}
