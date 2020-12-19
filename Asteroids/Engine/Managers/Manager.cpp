#include "Engine/Managers/Manager.hpp"
#include <algorithm>

Manager::~Manager() {
    // TODO: The moment we need more than 1 manager to have the same entity, we cant do this anymore
    std::for_each(entitiesMap.begin(), entitiesMap.end(), [](const auto& pair) {
        delete pair.first;
    });
    entitiesMap.clear();
}

void Manager::addEntity(Entity* entity) {
    entitiesMap.insert(std::pair<Entity*, ManagerInformation>(entity, ManagerInformation()));
}

void Manager::clean(Entity* entity) {
    const auto iterator = entitiesMap.find(entity);
    if(iterator != entitiesMap.end()) {
        iterator->second.state = ManagerInformation::State::Destroy;
    }
}

std::list<Entity*> Manager::flush() {
    std::list<Entity*> flushedEntities;
    for(auto iter = entitiesMap.begin(); iter != entitiesMap.end();) {
        if(iter->second.state == ManagerInformation::State::Destroy) {
            flushedEntities.push_back(iter->first);
            iter = entitiesMap.erase(iter);
        }
        else {
            ++iter;
        }
    }
    return flushedEntities;
}

void Manager::render(SDL_Renderer& renderer) {
    std::for_each(entitiesMap.begin(), entitiesMap.end(), [&renderer](const auto& pair) {
        pair.first->render(renderer);
    });
}

void Manager::update(float deltaTime) {
    std::for_each(entitiesMap.begin(), entitiesMap.end(), [=](const auto& pair) {
        pair.first->update(deltaTime);
    });
}

void Manager::update(const SDL_Event& event) {
    std::for_each(entitiesMap.begin(), entitiesMap.end(), [&event](const auto& pair) {
        pair.first->update(event);
    });
}
