#include "Engine/Components/FontComponent.hpp"
#include <Eigen/Dense>
#include <iostream>

FontComponent::FontComponent(const std::string& fontPath) : fontPath(fontPath) {
}

FontComponent::~FontComponent() {
    clean();
}

void FontComponent::clean() {
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

void FontComponent::setSize(int size) {
    this->size = size;
    isDirty = true;
}

void FontComponent::setText(std::string text) {
    this->text = text;
    isDirty = true;
}

void FontComponent::render(SDL_Renderer& renderer) {
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
    
    Eigen::Vector2f position = ownerEntity->getPosition() + this->position;

    SDL_Rect rectangle;
    rectangle.x = position.x();
    rectangle.y = position.y();
    SDL_QueryTexture(texture, nullptr, nullptr, &rectangle.w, &rectangle.h);
    SDL_RenderCopy(&renderer, texture, nullptr, &rectangle);
}