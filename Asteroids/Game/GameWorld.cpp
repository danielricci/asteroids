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

#include "Engine/Managers/InputManager.hpp"

#include "Game/GameWindow.hpp"

GameWorld::GameWorld(SDL_Window& window, SDL_Renderer& renderer) : window(window), renderer(renderer) {
    InputManager::getInstance();
    initialize();
}

GameWorld::~GameWorld() {
    destroy();
}

void GameWorld::clean() {
    for(Entity* entity : entities) {
        if(entity != nullptr) {
            delete entity;
            entity = nullptr;
        }
    }
    entities.clear();
}

void GameWorld::destroy() {
    clean();
    delete InputManager::getInstance();
}

void GameWorld::initialize() {
}

void GameWorld::run() {
    isRunning = true;
    while(isRunning) {
        processInput();
        if(isRunning) {
            update(gameWorldClock.sample());
            render();
        }
    }
}

void GameWorld::processInput() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
            isRunning = false;
            break;
        }
    }
}

void GameWorld::update(float deltaTime) const {
    // For now values of delta times that are greater than 1
    // or less than 120hz are clamped to 1/60. Issues arise when
    // the application first opens, and when the window is fully behind
    // another window, the deltaTime gets very very fast
    if(deltaTime < 0.0083 || deltaTime > 1) {
        deltaTime = 1.f / 60.f;
    }
}

void GameWorld::render() const {
    SDL_SetRenderDrawColor(&renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(&renderer);
    SDL_RenderPresent(&renderer);
}
