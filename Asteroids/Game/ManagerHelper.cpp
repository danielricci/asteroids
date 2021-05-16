#include "Engine/Managers/GameManager.hpp"
#include "Engine/Managers/InputManager.hpp"
#include "Engine/Managers/SoundManager.hpp"
#include "Engine/Managers/ViewManager.hpp"
#include "Engine/Managers/WindowManager.hpp"
#include "Game/ManagerHelper.hpp"
#include "Game/Views/GameView.hpp"
#include "Game/Views/HomeView.hpp"
#include <iostream>
#include <SDL.h>
#include <set>
#include <typeinfo>

std::list<Manager*> ManagerHelper::managers {};
bool ManagerHelper::isReset = false;

ManagerHelper::~ManagerHelper() {
    clean();
}

void ManagerHelper::add(Manager* manager) {
    if(manager != nullptr) {
        managers.push_back(manager);
    }
}

void ManagerHelper::beforeUpdate() {
    if(isReset) {
        isReset = false;
        reload();
    }
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
            delete manager;
            manager = nullptr;
        }
    }
    SDL_Quit();
}

void ManagerHelper::reload() {
    for(Manager* manager : managers) {
        if(manager != nullptr) {
            manager->clean();
        }
    }
}

void ManagerHelper::destroy(Entity* entity) {
    if(entity != nullptr) {
        for(Manager* manager : managers) {
            if(manager != nullptr) {
                manager->setState(entity, ManagerInformation::State::Destroy);
            }
        }
    }
}

SDL_Renderer* ManagerHelper::getRenderer() {
    return get<WindowManager>()->getRenderer();
}

void ManagerHelper::initialize() {
    add(new WindowManager());
    add(new InputManager());
    add(new SoundManager());
    add(new GameManager());
    
    HomeView* homeView = new HomeView();
    ViewManager* viewManager = new ViewManager({homeView, new GameView()});
    add(viewManager);
    viewManager->setActiveView(homeView->getViewName());
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

void ManagerHelper::reset() {
    isReset = true;
}

void ManagerHelper::setFeedbackState(Entity* entity, bool feedBack) {
    if(entity != nullptr) {
        ManagerInformation::State state;
        if(feedBack) {
            state = ManagerInformation::State::Enabled;
        }
        else {
            state = ManagerInformation::State::Disabled;
        }

        for(Manager* manager : managers) {
            if(manager != nullptr) {
                manager->setState(entity, state);
            }
        }
    }
}

void ManagerHelper::update(float deltaTime) {
    // Delta time update on all resources held by the managers
    for(Manager* manager : managers) {
        if(manager != nullptr) {
            manager->update(deltaTime);
        }
    }
    
    // Collision detection
    // Note: for now its done with the game manager
    get<GameManager>()->handleCollision();
    
    // Cleanup of objects. This cleanup goes through all
    // the managers to come up with the final list before
    // properly removing them
    std::set<Entity*> entitiesToDelete;
    for(Manager* manager : managers) {
        if(manager != nullptr) {
            std::list<Entity*> flushedEntities = manager->syncEntities();
            std::copy(flushedEntities.begin(), flushedEntities.end(), std::inserter(entitiesToDelete, entitiesToDelete.begin()));
        }
    }
    std::for_each(entitiesToDelete.begin(), entitiesToDelete.end(), [](Entity* entity) {
        std::cout << "[Game] - Deleting Resource: " << typeid(*entity).name()  << std::endl;
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
