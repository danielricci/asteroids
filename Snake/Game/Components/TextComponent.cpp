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

#include "Game/Components/TextComponent.hpp"

#include <iostream>

TextComponent::TextComponent(GameObject* gameObject, int size, bool bold, bool italic) : Component(gameObject) {
    font = TTF_OpenFont(fontPath, size);
    if(font == nullptr) {
        std::cerr << "Could not open the specified font: " << text << std::endl;
    }
    else {
        TTF_SetFontStyle(font, (TTF_STYLE_BOLD & (bold ? 0xF : 0x0)) | (TTF_STYLE_ITALIC & (italic ? 0xF : 0x0)));
        createSurface();
    }
}

TextComponent::~TextComponent() {
    if(surface != nullptr) {
        SDL_FreeSurface(surface);
        surface = nullptr;
    }
    if(font != nullptr) {
        TTF_CloseFont(font);
        font = nullptr;
    }
}

void TextComponent::createSurface() {
    if(surface != nullptr) {
        SDL_FreeSurface(surface);
    }
    surface = TTF_RenderText_Blended(font, text.c_str(), color);
}

void TextComponent::setText(const std::string& text) {
    if(this->font == nullptr) {
        std::cerr << "Font is invalid, cannot set the specified text" << std::endl;
    }
    else if(surface == nullptr || this->text != text) {
        this->text = text;
        createSurface();
    }
}
