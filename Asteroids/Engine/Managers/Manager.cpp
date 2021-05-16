#include "Engine/Managers/Manager.hpp"

Manager::~Manager() {
    clean();
}

void Manager::addEntity(Entity* entity) {
    entities.insert(std::pair<Entity*, ManagerInformation>(entity, ManagerInformation()));
}

void Manager::clean() {
    std::for_each(entities.begin(), entities.end(), [](const auto& pair) {
        delete pair.first;
    });
    entities.clear();
}

bool Manager::setState(Entity* entity, ManagerInformation::State state) {
    if(entity != nullptr) {
        const auto iterator = entities.find(entity);
        if(iterator != entities.end()) {
            iterator->second.state = state;
            return true;
        }
    }
    
    return false;
}

void Manager::render(SDL_Renderer& renderer) {
    std::for_each(entities.begin(), entities.end(), [&renderer](const auto& pair) {
        if(pair.second.state != ManagerInformation::State::Destroy && pair.second.state != ManagerInformation::State::Disabled) {
            pair.first->render(renderer);
        }
    });
}

std::list<Entity*> Manager::syncEntities() {
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

void Manager::update(float deltaTime) {
    std::for_each(entities.begin(), entities.end(), [=](const auto& pair) {
        if(pair.second.state != ManagerInformation::State::Destroy && pair.second.state != ManagerInformation::State::Disabled) {
            pair.first->update(deltaTime);
        }
    });
}

void Manager::update(const SDL_Event& event) {
    std::for_each(entities.begin(), entities.end(), [&event](const auto& pair) {
        if(pair.second.state != ManagerInformation::State::Destroy && pair.second.state != ManagerInformation::State::Disabled) {
            pair.first->update(event);
        }
    });
}
