#include "Engine/Components/TextComponent.hpp"

#include <iostream>

TextComponent::TextComponent(Entity* entity, int size, bool bold, bool italic) : Component(entity) {
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
