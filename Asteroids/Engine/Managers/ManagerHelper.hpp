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
    
    static void initialize(SDL_Window& window);
    static void clean();
    static void update(float deltaTime);
    static void update(const SDL_Event& event);
    static void render(SDL_Renderer& renderer);
private:
    ManagerHelper() = default;
    virtual ~ManagerHelper();
    static std::list<Manager*> managers;
};
