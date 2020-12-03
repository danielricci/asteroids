#include "Engine/Managers/Manager.hpp"

Manager::~Manager() {
    //clearNodes();
}

void Manager::addEntity(Entity* entity) {
    //this->nodes.push_back(node);
}

void Manager::removeEntity(Entity* entity) {
    //this->retiredNodes.push_back(node);
}

void Manager::clear() {
//    finish();
//    for(Node* node : this->nodes) {
//        if(node != nullptr) {
//            delete node;
//        }
//    }
//    nodes.clear();
}

void Manager::update(float deltaTime) {
//    for(Node* node : this->nodes) {
//        if(node != nullptr) {
//            Entity* entity = dynamic_cast<Entity*>(node);
//            if(entity != nullptr) {
//                entity->update(deltaTime);
//            }
//        }
//    }
}

void Manager::update(const SDL_Event& event) {
//    for(Node* node : this->nodes) {
//        if(node != nullptr) {
//            Entity* entity = dynamic_cast<Entity*>(node);
//            if(entity != nullptr) {
//                entity->update(event);
//            }
//        }
//    }
}

void Manager::render(SDL_Renderer& renderer) {
//    for(Node* node : this->nodes) {
//        if(node != nullptr) {
//            Entity* entity = dynamic_cast<Entity*>(node);
//            if(entity != nullptr) {
//                entity->render(renderer);
//            }
//        }
//    }
}

void Manager::finish() {
//    for(Node* node : retiredNodes) {
//        if(node != nullptr) {
//            nodes.remove(node);
//            delete node;
//        }
//    }
//    
//    retiredNodes.clear();
}
