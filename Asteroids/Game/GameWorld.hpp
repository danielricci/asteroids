/**
* MIT License
*
* Copyright (c) 2020 Daniel Ricci {@literal <thedanny09@icloud.com>}
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#pragma once

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
    void draw() const;
    
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
    
    void clean();
    void initialize();
    void destroy();
    
    bool isGameQuit = false;
    bool isGameRunning = false;
    
    std::list<Entity*> entities;
    
    SDL_Window& window;
    SDL_Renderer& renderer;
};
