#include "Engine/Managers/Manager.hpp"

void Manager::addNode(Node* node) {
    this->nodes.push_back(node);
}

void Manager::update(float deltaTime) {
}

void Manager::update(const SDL_Event& event) {
}

void Manager::render(SDL_Renderer& renderer) {
}
