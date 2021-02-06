#include "Engine/Components/TextComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include <iostream>

TextComponent::TextComponent(const std::string& fontPath) : fontPath(fontPath) {
}

TextComponent::~TextComponent() {
    clean();
}

void TextComponent::clean() {
    if(font != nullptr) {
        TTF_CloseFont(font);
        font = nullptr;
    }
    if(texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    if(surface != nullptr) {
        SDL_FreeSurface(surface);
        surface = nullptr;
    }
}

void TextComponent::setSize(int size) {
    this->size = size;
}

void TextComponent::setText(std::string text) {
    this->text = text;
}

void TextComponent::render(SDL_Renderer& renderer) {
//    if(!this->getIsVisible() || !isDirty) {
//        return;
//    }

    isDirty = false;
    clean();
    
    font = TTF_OpenFont(fontPath.c_str(), this->size);
    if(font == nullptr) {
        std::cerr << "Could not open the specified font" << std::endl;
        return;
    }

    surface = TTF_RenderText_Blended(font, text.c_str(), this->color);
    if(surface == nullptr) {
        std::cerr << "Could not create the surface from the specified font" << std::endl;
        return;
    }

    texture = SDL_CreateTextureFromSurface(&renderer, surface);
    if(texture == nullptr) {
        std::cerr << "Could not create the texture from the specified surface" << std::endl;
        return;
    }
    
    Eigen::Vector2f position = this->ownerEntity->getPosition();

    SDL_Rect rectangle;
    rectangle.x = position.x();
    rectangle.y = position.y();
    SDL_QueryTexture(texture, nullptr, nullptr, &rectangle.w, &rectangle.h);
    SDL_RenderCopy(&renderer, texture, nullptr, &rectangle);
}
