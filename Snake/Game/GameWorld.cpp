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

#include "Game/GameObjects/FoodObject.hpp"
#include "Game/GameObjects/GameOverObject.hpp"
#include "Game/GameObjects/SnakeObject.hpp"
#include "Game/GameWindow.hpp"
#include "Game/Managers/InputManager.hpp"

GameWorld::GameWorld(SDL_Window& window, SDL_Renderer& renderer) : window(window), renderer(renderer) {
    InputManager::getInstance();
    
    int width = 0;
    int height = 0;
    SDL_GetWindowSize(&window, &width, &height);
    
    movementSystem = new MovementSystem(window);
    renderSystem = new RenderSystem(renderer);
    
    initialize();
}

GameWorld::~GameWorld() {
    destroy();
}

void GameWorld::clean() {
    for(GameObject* gameObject : gameObjects) {
        delete gameObject;
        gameObject = nullptr;
    }
    gameObjects.clear();
    
    isGameRunning = true;
    isGameQuit = false;
}

void GameWorld::destroy() {
    InputManager::getInstance()->terminate();

    if(renderSystem != nullptr) {
        delete renderSystem;
        renderSystem = nullptr;
    }
    
    if(movementSystem != nullptr) {
        delete movementSystem;
        movementSystem = nullptr;
    }
    
    clean();
}

void GameWorld::initialize() {
    SnakeObject* snakeObject = new SnakeObject(SnakeBodyComponent::CELL_WIDTH, 20 * SnakeBodyComponent::CELL_HEIGHT, isGameMode2);
    gameObjects.push_back(snakeObject);
    
    FoodObject* foodObject = new FoodObject(0 /* unused */, 0 /* unused */, SnakeBodyComponent::CELL_WIDTH, SnakeBodyComponent::CELL_HEIGHT);
    movementSystem->processFoodPosition(snakeObject, foodObject);
    gameObjects.push_back(foodObject);
    
    // Note: This should be pushed last so it renders last
    gameObjects.push_back(new GameOverObject(window, renderer));
}

void GameWorld::run() {
    
    SDL_TimerID timerId = SDL_AddTimer(tickSpeed, [](Uint32 interval, void* param) -> Uint32 {
        SDL_UserEvent userevent;
        userevent.type = SDL_USEREVENT;
        userevent.code = 0;
        userevent.data1 = NULL;
        userevent.data2 = NULL;

        SDL_Event event;
        event.type = SDL_USEREVENT;
        event.user = userevent;

        SDL_PushEvent(&event);
        
        GameWorld* gameWorld = static_cast<GameWorld*>(param);
        return gameWorld->tickSpeed;
    }, this);

    // Perform an initial draw to show everything on screen
    draw();
        
    while(!isGameQuit) {
        SDL_Event event;
        while(SDL_PollEvent(&event) != 0) {
            if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
                SDL_RemoveTimer(timerId);
                isGameQuit = true;
                break;
            }
            
            if(event.type == SDL_KEYUP) {
                if(getGameObject<GameOverObject>()->getIsGameOver() && event.key.keysym.sym == SDLK_RETURN) {
                    clean();
                    initialize();
                    break;
                }
                            
                switch(event.key.keysym.sym) {
                    case SDLK_SPACE: {
                        isGameRunning = !isGameRunning;
                        break;
                    }
                    case SDLK_F1: {
                        int newSpeed = this->tickSpeed - 100;
                        if(newSpeed >= 100) {
                            this->tickSpeed = newSpeed;
                        }
                        break;
                    }
                    case SDLK_F2: {
                        int newSpeed = this->tickSpeed + 100;
                        if(newSpeed <= 1000) {
                            this->tickSpeed = newSpeed;
                        }
                        break;
                    }
                    case SDLK_F3: {
                        FoodObject* foodObject = getGameObject<FoodObject>();
                        movementSystem->processFoodPosition(getGameObject<SnakeObject>(), foodObject);
                        Eigen::Vector2f positionVector = foodObject->getComponent<TransformComponent>()->positionVector;
                        break;
                    }
                    case SDLK_F4: {
                        isGameMode2 = !isGameMode2;
                        clean();
                        initialize();
                        break;
                    }
                    default: {
                        if(!isGameRunning) {
                            isGameRunning = true;
                        }
                    }
                }
            }

            // Process any inputs
            InputManager::getInstance()->process(event, getGameComponents<SnakeObject, InputComponent>());

            // Handle the user event
            if(isGameRunning && event.type == SDL_USEREVENT) {
                if(!getGameObject<GameOverObject>()->getIsGameOver()) {
                    movementSystem->process(this->getGameObject<SnakeObject>(), this->getGameObject<FoodObject>(), this->getGameObject<GameOverObject>());
                    draw();
                }
            }
        }
    }
}

void GameWorld::draw() const {
    // Clear the back buffer to prepare it for rendering
    SDL_SetRenderDrawColor(&renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(&renderer);
    
    // Render System
    renderSystem->process(gameObjects);
    
    // Blit everything onto the display
    SDL_RenderPresent(&renderer);
}
