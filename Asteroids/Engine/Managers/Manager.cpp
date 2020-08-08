#include "Engine/Managers/Manager.hpp"

void Manager::addEntity(Entity* entity) {
    this->entities.push_back(entity);
}

void Manager::update(float deltaTime) {
}

void Manager::update(const SDL_Event& event) {
}

void Manager::render(SDL_Renderer& renderer) {
}
