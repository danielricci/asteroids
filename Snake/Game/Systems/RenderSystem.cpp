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

#include "Game/Components/RenderComponent.hpp"
#include "Game/Components/SnakeBodyComponent.hpp"
#include "Game/Components/TransformComponent.hpp"
#include "Game/Components/TextComponent.hpp"
#include "Game/Components/TextRenderComponent.hpp"
#include "Game/Systems/RenderSystem.hpp"

RenderSystem::RenderSystem(SDL_Renderer& renderer) : renderer(renderer) {
}

void RenderSystem::process(const std::list<GameObject*> gameObjects) {
    this->gameObjects = gameObjects;
    for(GameObject* gameObject : gameObjects) {
        process(gameObject);
    }
}

void RenderSystem::process(GameObject* gameObject) {
    if(gameObject != nullptr) {
        RenderComponent* renderComponent = gameObject->getComponent<RenderComponent>();
        if(renderComponent != nullptr && renderComponent->isVisible) {
            TextComponent* textComponent = gameObject->getComponent<TextComponent>();
            TextRenderComponent* textRenderComponent = gameObject->getComponent<TextRenderComponent>();
            if (textComponent != nullptr && textRenderComponent != nullptr) {
                SDL_Rect rectangle = gameObject->getComponent<TransformComponent>()->getRectangle();
                SDL_QueryTexture(textRenderComponent->getTexture(), nullptr, nullptr, &rectangle.w, &rectangle.h);
                SDL_RenderCopy(&renderer, textRenderComponent->getTexture(), nullptr, &rectangle);
            }
            else {
                SnakeObject* snakeObject = dynamic_cast<SnakeObject*>(gameObject);
                if(snakeObject != nullptr) {
                    processSnakeRender(*snakeObject);
                }
                else {
                    FoodObject* foodObject = dynamic_cast<FoodObject*>(gameObject);
                    if(foodObject != nullptr) {
                        processFoodRender(*foodObject);
                    }
                }
            }
        }
    }
}

void RenderSystem::processSnakeRender(const SnakeObject& snakeObject) {
    
    SnakeBodyComponent* snakeBodyComponent = snakeObject.getComponent<SnakeBodyComponent>();
    Eigen::Vector2f worldPosition = snakeBodyComponent->getGameObject()->getComponent<TransformComponent>()->positionVector;
    
    std::deque<TransformComponent*>::iterator snakeBodyTailIterator = snakeBodyComponent->getTailIterator();
    while(snakeBodyTailIterator != snakeBodyComponent->getHeadIterator()) {
        SDL_Rect rectangle;
        rectangle.x = worldPosition.x() + (*snakeBodyTailIterator)->positionVector.x();
        rectangle.y = worldPosition.y() + (*snakeBodyTailIterator)->positionVector.y();
        rectangle.w = SnakeBodyComponent::CELL_WIDTH;
        rectangle.h = SnakeBodyComponent::CELL_HEIGHT;
    
        if(*snakeBodyTailIterator != snakeBodyComponent->getHead()) {
            SDL_SetRenderDrawColor(&renderer, 0x00, 0xFF, 0x00, SDL_ALPHA_OPAQUE);
        }
        else {
            SDL_SetRenderDrawColor(&renderer, 0xFF, 0x00, 0x00, SDL_ALPHA_OPAQUE);
        }
        SDL_RenderFillRect(&renderer, &rectangle);
        
        ++snakeBodyTailIterator;
    }
}

void RenderSystem::processFoodRender(const FoodObject& foodObject) {
    SDL_SetRenderDrawColor(&renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_Rect rectangle = foodObject.getComponent<TransformComponent>()->getRectangle();
    SDL_RenderFillRect(&renderer, &rectangle);
}
