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

#include "Game/Components/CollisionComponent.hpp"
#include "Game/Components/RenderComponent.hpp"
#include "Game/GameObjects/GameObject.hpp"
#include "Game/Components/SoundComponent.hpp"

class BallObject : public GameObject {

public:
    inline static const int WIDTH { 9 };
    inline static const int HEIGHT { 9 };
    inline static const float INITIAL_VELOCITY_X { 9 };
    inline static const float INITIAL_VELOCITY_Y { 0 };
    
    BallObject(int x, int y);
    
    void playPaddleHitSound() const;
    void playScoreSound() const;
    void playWallHitSound() const;
    
private:
    CollisionComponent* collisionComponent = new CollisionComponent();
    RenderComponent* renderComponent = new RenderComponent();
    
    SoundComponent* paddleHitSound { nullptr };
    SoundComponent* scoreSound { nullptr };
    SoundComponent* wallHitSound { nullptr };
};
