#include "Engine/Managers/Manager.hpp"

void Manager::addEntity(Entity* entity) {
    entities.insert(std::pair<Entity*, ManagerInformation>(entity, ManagerInformation()));
}

void Manager::clean() {
    // TODO: The moment we need more than 1 manager to have the same entity, we cant do this anymore
    std::for_each(entities.begin(), entities.end(), [](const auto& pair) {
        delete pair.first;
    });
    entities.clear();
}

void Manager::removeEntity(Entity* entity) {
    const auto iterator = entities.find(entity);
    if(iterator != entities.end()) {
        iterator->second.state = ManagerInformation::State::Destroy;
    }
}

std::list<Entity*> Manager::purgeEntities() {
    std::list<Entity*> flushedEntities;
    for(auto iter = entities.begin(); iter != entities.end();) {
        if(iter->second.state == ManagerInformation::State::Destroy) {
            flushedEntities.push_back(iter->first);
            iter = entities.erase(iter);
        }
        else {
            ++iter;
        }
    }
    return flushedEntities;
}

void Manager::render(SDL_Renderer& renderer) {
    std::for_each(entities.begin(), entities.end(), [&renderer](const auto& pair) {
        pair.first->render(renderer);
    });
}

void Manager::update(float deltaTime) {
    std::for_each(entities.begin(), entities.end(), [=](const auto& pair) {
        if(pair.second.state != ManagerInformation::State::Destroy) {
            pair.first->update(deltaTime);
        }
    });
}

void Manager::update(const SDL_Event& event) {
    std::for_each(entities.begin(), entities.end(), [&event](const auto& pair) {
        if(pair.second.state != ManagerInformation::State::Destroy) {
            pair.first->update(event);
        }
    });
}
