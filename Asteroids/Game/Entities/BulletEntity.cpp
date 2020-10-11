#include "Engine/Components/RenderComponent.hpp"
#include "Engine/Components/CircleComponent.hpp"
#include "Game/Entities/BulletEntity.hpp"

BulletEntity::BulletEntity() {
    this->addNode(new RenderComponent());
    this->addNode(new CircleComponent({40, 40}, 10));
}

void BulletEntity::render(SDL_Renderer& renderer) {
    this->getNode<CircleComponent>()->render(renderer);
}
