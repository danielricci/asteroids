#pragma once

#include "Engine/Managers/Manager.hpp"

#include <SDL.h>

#include <list>

class ManagerHelper {
public:
    template<typename T> static T* get() {
        for(Manager* manager : managers) {
            T* object = dynamic_cast<T*>(manager);
            if(object != nullptr) {
                return object;
            }
        }
        return nullptr;
    }
    static void processEvent(const SDL_Event& event);
    static void initialize(SDL_Renderer& renderer);
    static void clean();
private:
    ManagerHelper() = default;
    ~ManagerHelper() {
        clean();
    }
    static std::list<Manager*> managers;
};
