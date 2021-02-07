#pragma once

#include "Engine/Entities/Entity.hpp"
#include "Engine/Managers/Manager.hpp"
#include "Engine/System/EventArgs.hpp"
#include <SDL.h>
#include <list>

class ManagerHelper {
public:
    enum BroadcastEvent {
        EVENT_ASTEROID_HIT = 0
    };
    
    static void broadcast(BroadcastEvent broadcastEvent, void* sender, const EventArgs& args);
    static void clean();
    static void clean(Entity* obj);
    static SDL_Renderer* getRenderer();
    static void initialize(const char* const title, int width, int height);
    static void render();
    static void update(float deltaTime);
    static void update(const SDL_Event& event);
    
    template<typename T> static T* get() {
        for(Manager* manager : managers) {
            T* object = dynamic_cast<T*>(manager);
            if(object != nullptr) {
                return object;
            }
        }
        return nullptr;
    }
private:
    ManagerHelper() = default;
    ~ManagerHelper();
    
    static std::list<Manager*> managers;
};
