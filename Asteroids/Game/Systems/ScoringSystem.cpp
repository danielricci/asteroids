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

#include "Game/Systems/ScoringSystem.hpp"
#include "Game/Components/TextComponent.hpp"
#include "Game/Components/TransformComponent.hpp"

#include <cmath>
#include <iostream>

ScoringSystem::ScoringSystem(SDL_Window& window) {
    SDL_GetWindowSize(&window, &worldWidth, &worldHeight);
}

ScoringSystem::~ScoringSystem() {
    if(gameOverSound != nullptr) {
        delete gameOverSound;
        gameOverSound = nullptr;
    }
}

void ScoringSystem::process(BallObject& ballObject, const std::list<ScoreObject*>& scoreObjects, GameOverObject& gameOverObject) const {
    TransformComponent* ballTransformComponent { ballObject.getTransform() };
    if(ballTransformComponent->positionVector.x() <= 0 || ballTransformComponent->positionVector.x() + ballTransformComponent->dimensionVector.x() >= worldWidth) {
        ScoreObject* farthestScoreObject { nullptr };
        for(ScoreObject* scoreObject : scoreObjects) {
            if(farthestScoreObject == nullptr || std::abs(scoreObject->getPaddleObject()->getTransform()->positionVector.x() - ballTransformComponent->positionVector.x()) > std::abs(farthestScoreObject->getPaddleObject()->getTransform()->positionVector.x() - ballTransformComponent->positionVector.x())) {
                farthestScoreObject = scoreObject;
            }
        }
        if(farthestScoreObject != nullptr) {
            farthestScoreObject->setScore(farthestScoreObject->getScore() + 1);
            ballObject.playScoreSound();
    
            if(farthestScoreObject->getScore() >= MAX_GAME_SCORE) {
                gameOverObject.setIsGameOver(true);
                gameOverSound->play(5);
            }
        }
    }
}
