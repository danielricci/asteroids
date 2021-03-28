#include "Engine/Components/ShapeComponent.hpp"
#include "Game/Particles/PlayerExplosionParticle.hpp"

PlayerExplosionParticle::PlayerExplosionParticle(PlayerEntity* playerEntity) {
    setPosition(playerEntity->getPosition());

    this->playerEntity = playerEntity;
    ShapeComponent* playerShape = this->playerEntity->getComponent<ShapeComponent>(PlayerEntity::PLAYER_SHIP);
    if(playerShape != nullptr) {
        for(int i = 0; i < playerShape->getSize() - 1; ++i) {
            edges.push_back(std::pair<Eigen::Vector2f, Eigen::Vector2f>((*playerShape)[i], (*playerShape)[i + 1]));
        }
    }
}

void PlayerExplosionParticle::render(SDL_Renderer& renderer) {
    for(const auto& edge : edges) {
        Eigen::Vector2f position1 = getPosition(edge.first);
        Eigen::Vector2f position2 = getPosition(edge.second);
        SDL_RenderDrawLineF(&renderer, position1.x(), position1.y(), position2.x(), position2.y());
    }
}

void PlayerExplosionParticle::setOrientation(int orientation) {
    GameEntity::setOrientation(orientation);
}

void PlayerExplosionParticle::update(float deltaTime) {
    // TODO: update
}

void PlayerExplosionParticle::update(const SDL_Event& event) {
    
}
