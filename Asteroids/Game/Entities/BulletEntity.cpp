#include "Engine/Components/CircleComponent.hpp"
#include "Engine/Components/RenderComponent.hpp"
#include "Engine/Managers/ManagerHelper.hpp"
#include "Engine/Managers/GameManager.hpp"
#include "Game/Entities/BulletEntity.hpp"
#include "Game/Entities/PlayerEntity.hpp"

BulletEntity::BulletEntity() {
    this->addNode(new RenderComponent());
    this->addNode(new CircleComponent({40, 40}, 1));
}

void BulletEntity::render(SDL_Renderer& renderer) {
    this->getNode<CircleComponent>()->render(renderer);
}

void BulletEntity::update(float deltaTime) {
    
}
