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

#include "Game/Components/SoundComponent.hpp"

#include <iostream>

SoundComponent::SoundComponent(const std::string& path) : path(path) {
    chunk = Mix_LoadWAV(path.c_str());
    if(chunk == nullptr) {
        std::cerr << "Could not load sound at path " << path << "because of error:" << Mix_GetError() << std::endl;
    }
}

SoundComponent::~SoundComponent() {
    if(chunk != nullptr) {
        Mix_FreeChunk(chunk);
        chunk = nullptr;
    }
}

void SoundComponent::play(int loops) const {
    if(chunk != nullptr) {
        Mix_PlayChannel(-1, chunk, loops);
    }
    else {
        std::cerr << "Could not play sound, invalid chunk" << std::endl;
    }
}
