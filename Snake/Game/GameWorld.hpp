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

#include "Game/GameObjects/GameObject.hpp"
#include "Game/GameWindow.hpp"
#include "Game/Systems/RenderSystem.hpp"
#include "Game/Systems/MovementSystem.hpp"

#include <SDL.h>

#include <list>

class GameWorld {
public:
    GameWorld(SDL_Window& window, SDL_Renderer& renderer);
    ~GameWorld();
    
    void run();
private:
    void draw() const;
    
    template<typename T> T* getGameObject() {
        for(GameObject* gameObject : gameObjects) {
            T* object = dynamic_cast<T*>(gameObject);
            if(object != nullptr) {
                return object;
            }
        }
        return nullptr;
    }
    
    template<typename T> std::list<T*> getGameObjects() {
        std::list<T*> objects;
        for(GameObject* gameObject : gameObjects) {
            T* object = dynamic_cast<T*>(gameObject);
            if(object != nullptr) {
                objects.push_back(object);
            }
        }
        return objects;
    }
    
    template<typename T, typename U> std::list<U*> getGameComponents() {
        std::list<U*> components;
        for(GameObject* gameObject : gameObjects) {
            T* object = dynamic_cast<T*>(gameObject);
            if(object != nullptr) {
                U* component = gameObject->getComponent<U>();
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
    
    int tickSpeed = 100;
    bool isGameQuit = false;
    bool isGameRunning = false;
    bool isGameMode2 = false;
    
    std::list<GameObject*> gameObjects;
    
    SDL_Window& window;
    SDL_Renderer& renderer;
    
    RenderSystem* renderSystem =  nullptr;
    MovementSystem* movementSystem = nullptr;
};
