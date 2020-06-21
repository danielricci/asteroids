#pragma once

#include "Engine/Core/Clock.hpp"
#include "Engine/Entities/Entity.hpp"

#include "Game/GameWindow.hpp"

#include <SDL.h>

#include <list>

class GameWorld {
public:
    GameWorld(SDL_Window& window, SDL_Renderer& renderer);
    ~GameWorld();
    
    void run();
private:
    template<typename T> T* getEntity() {
        for(Entity* entity : entities) {
            T* object = dynamic_cast<T*>(entity);
            if(object != nullptr) {
                return object;
            }
        }
        return nullptr;
    }
    
    template<typename T> std::list<T*> getEntities() {
        std::list<T*> objects;
        for(Entity* entity : entities) {
            T* object = dynamic_cast<T*>(entity);
            if(object != nullptr) {
                objects.push_back(object);
            }
        }
        return objects;
    }
    
    template<typename T, typename U> std::list<U*> getGameComponents() {
        std::list<U*> components;
        for(Entity* entity : entities) {
            T* object = dynamic_cast<T*>(entity);
            if(object != nullptr) {
                U* component = entity->getComponent<U>();
                if(component != nullptr) {
                    components.push_back(component);
                }
            }
        }
        return components;
    }
    
    void processInput();
    void render() const;
    void update(float deltaTime) const;
    
    void clean();
    void destroy();
    void initialize();

    std::list<Entity*> entities;
    
    SDL_Window& window;
    SDL_Renderer& renderer;
    
    Clock gameWorldClock;
    
    bool isRunning = false;
};
