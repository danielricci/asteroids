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

#include "Game/GameObjects/GameOverObject.hpp"

#include "Game/Components/RenderComponent.hpp"
#include "Game/Components/TransformComponent.hpp"

GameOverObject::GameOverObject(SDL_Window& window, SDL_Renderer& renderer) {
    textRenderComponent = new TextRenderComponent(this, renderer);
    addComponent(this->textRenderComponent);
    
    textComponent->setText(GAME_OVER);
    textRenderComponent->createTexture(*textComponent->getSurface());
    addComponent(this->textComponent);
    
    // Set the position of this object
    int windowWidth = 0;
    int windowHeight = 0;
    SDL_GetWindowSize(&window, &windowWidth, &windowHeight);
    TransformComponent* transformComponent = getComponent<TransformComponent>();
    transformComponent->positionVector.x() = (windowWidth / 2) - (textComponent->getSurface()->w / 2);
    transformComponent->positionVector.y() = (windowHeight / 3) - (textComponent->getSurface()->h / 2);
    
    // Indicate that it is not a game over
    setIsGameOver(false);
}

void GameOverObject::setIsGameOver(bool isGameOver) {
    this->isGameOver = isGameOver;
    this->textRenderComponent->isVisible = isGameOver;
}
