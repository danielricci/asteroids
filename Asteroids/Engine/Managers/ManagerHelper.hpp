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
    
    static void initialize(const char* const title, int width, int height);
    
    static void clean();
    static void finish();
    static SDL_Renderer* getRenderer();
    static void update(float deltaTime);
    static void update(const SDL_Event& event);
    static void render();
private:
    ManagerHelper() = default;
    ~ManagerHelper();
    
    static std::list<Manager*> managers;
};
