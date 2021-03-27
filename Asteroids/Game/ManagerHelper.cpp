#include "Engine/Managers/GameManager.hpp"
#include "Engine/Managers/InputManager.hpp"
#include "Engine/Managers/UIManager.hpp"
#include "Engine/Managers/WindowManager.hpp"
#include "Game/ManagerHelper.hpp"
#include "Game/Entities/CopyrightEntity.hpp"
#include "Game/Entities/HighScoreEntity.hpp"
#include "Game/Entities/LivesEntity.hpp"
#include "Game/Entities/PlayerScoreEntity.hpp"
#include <SDL.h>
#include <set>

std::list<Manager*> ManagerHelper::managers {};

ManagerHelper::~ManagerHelper() {
    clean();
    SDL_Quit();
}

void ManagerHelper::broadcast(BroadcastEvent broadcastEvent, void* sender, const EventArgs& args) {
    SDL_UserEvent userevent;
    userevent.type = SDL_USEREVENT;
    userevent.code = static_cast<int>(broadcastEvent);
    userevent.data1 = sender;
    userevent.data2 = (void*)&args;

    SDL_Event event;
    event.type = SDL_USEREVENT;
    event.user = userevent;

    ManagerHelper::update(event);
}

void ManagerHelper::clean() {
    for(Manager* manager : managers) {
        if(manager != nullptr) {
            manager->clean();
        }
    }
    for(Manager* manager : managers) {
        if(manager != nullptr) {
            delete manager;
            manager = nullptr;
        }
    }
    managers.clear();
}

void ManagerHelper::clean(Entity* entity) {
    if(entity != nullptr) {
        for(Manager* manager : managers) {
            if(manager != nullptr) {
                manager->removeEntity(entity);
            }
        }
    }
}

SDL_Renderer* ManagerHelper::getRenderer() {
    return get<WindowManager>()->getRenderer();
}

void ManagerHelper::initialize(const char* const title, int width, int height) {
    clean();
    
    managers.push_back(new WindowManager(title, width, height));
    managers.push_back(new InputManager());
    
    UIManager* uiManager = new UIManager();
    uiManager->addEntity(new HighScoreEntity());
    uiManager->addEntity(new LivesEntity());
    uiManager->addEntity(new PlayerScoreEntity());
    uiManager->addEntity(new CopyrightEntity());
    managers.push_back(uiManager);
    
    GameManager* gameManager = new GameManager();
    gameManager->setGameState(GameManager::GameState::STARTED);
    managers.push_back(gameManager);
}

void ManagerHelper::render() {
    SDL_Renderer* renderer = ManagerHelper::getRenderer();
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    for(Manager* manager : managers) {
        if(manager != nullptr) {
            manager->render(*renderer);
        }
    }
    
    SDL_RenderPresent(renderer);
}

void ManagerHelper::update(float deltaTime) {
    for(Manager* manager : managers) {
        if(manager != nullptr) {
            manager->update(deltaTime);
        }
    }
    
    get<GameManager>()->handleCollision();
    
    std::set<Entity*> entitiesToDelete;
    for(Manager* manager : managers) {
        if(manager != nullptr) {
            std::list<Entity*> flushedEntities = manager->purgeEntities();
            std::copy(flushedEntities.begin(), flushedEntities.end(), std::inserter(entitiesToDelete, entitiesToDelete.begin()));
        }
    }
    std::for_each(entitiesToDelete.begin(), entitiesToDelete.end(), [](Entity* entity) {
        delete entity;
    });
}

void ManagerHelper::update(const SDL_Event& event) {
    for(Manager* manager : managers) {
        if(manager != nullptr) {
            manager->update(event);
        }
    }
}
