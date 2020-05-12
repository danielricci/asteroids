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

#include "Game/Components/Component.hpp"
#include "Game/Components/TransformComponent.hpp"

#include <Eigen/Dense>

#include <deque>

class SnakeBodyComponent : public Component {
public:
    SnakeBodyComponent(GameObject* gameObject);
    virtual ~SnakeBodyComponent();
  
    inline std::deque<TransformComponent*>::size_type getLength() const { return snakeBody.size(); }

    inline TransformComponent* getTail() { return snakeBody.front(); }
    inline TransformComponent* getHead() { return snakeBody.back(); }

    inline std::deque<TransformComponent*>::iterator getTailIterator() { return snakeBody.begin(); }
    inline std::deque<TransformComponent*>::iterator getHeadIterator() { return snakeBody.end(); }
    
    void moveTailToHead();
    void increaseSnakeLength(const Eigen::Vector2f& position);
    
    static const int CELL_WIDTH;
    static const int CELL_HEIGHT;
    
    bool isGameMode2 = false;
private:
    std::deque<TransformComponent*> snakeBody;
    
    static const int INITIAL_LENGTH;
};
