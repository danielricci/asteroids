#include "Engine/Components/TextComponent.hpp"
#include <Eigen/Dense>
#include <iostream>

TextComponent::TextComponent(const std::string& fontPath) : fontPath("Resources/" + fontPath) {
}

TextComponent::TextComponent(const std::string& fontPath, const std::string& text, int size) : TextComponent(fontPath) {
    this->text = text;
    this->size = size;
    this->isDirty = true;
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
    
    isDirty = true;
}

void TextComponent::setSize(int size) {
    this->size = size;
    isDirty = true;
}

void TextComponent::setText(std::string text) {
    this->text = text;
    isDirty = true;
}

void TextComponent::render(SDL_Renderer& renderer) {
    if(isDirty) {
        clean();
        isDirty = false;
        
        font = TTF_OpenFont(fontPath.c_str(), size);
        if(font == nullptr) {
            std::cerr << "Could not open the specified font" << std::endl;
            return;
        }

        surface = TTF_RenderText_Blended(font, text.c_str(), color);
        if(surface == nullptr) {
            std::cerr << "Could not create the surface from the specified font" << std::endl;
            return;
        }

        texture = SDL_CreateTextureFromSurface(&renderer, surface);
        if(texture == nullptr) {
            std::cerr << "Could not create the texture from the specified surface" << std::endl;
            return;
        }
    }
    
    if(!getIsVisible()) {
        return;
    }
    
    Eigen::Vector2f position = ownerEntity->getPosition() + this->position;

    SDL_Rect rectangle;
    rectangle.x = position.x();
    rectangle.y = position.y();
    SDL_QueryTexture(texture, nullptr, nullptr, &rectangle.w, &rectangle.h);
    SDL_RenderCopy(&renderer, texture, nullptr, &rectangle);
}
