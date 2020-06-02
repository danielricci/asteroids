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

#include "Game/GameWindow.hpp"

#include <iostream>

#include <SDL_ttf.h>

GameWindow::GameWindow(const char* title, int width, int height) {
    if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL video initialization failed: " << SDL_GetError() << std::endl;
        return;
    }
    
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if(window == nullptr) {
        std::cerr << "SDL window could not be created: " << SDL_GetError() << std::endl;
        return;
    }
    
    renderer = SDL_CreateRenderer(window, -1, 0);
    if(renderer == nullptr) {
        std::cerr << "SDL renderer could not be created: " << SDL_GetError() << std::endl;
        return;
    }

    if(TTF_Init() < 0) {
        std::cerr << "SDL_ttf could not be initialized: " << TTF_GetError() << std::endl;
        return;
    }
    
    gameWorld = new GameWorld(*window, *renderer);
}

GameWindow::~GameWindow() {
    if(gameWorld != nullptr) {
        delete gameWorld;
        gameWorld = nullptr;
    }

    if(renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    
    if(window != nullptr) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    TTF_Quit();
    SDL_Quit();
}

void GameWindow::show() const {
    if(gameWorld != nullptr) {
        gameWorld->run();
    }
}
