#include "Engine/Components/TextRenderComponent.hpp"

#include <iostream>

TextRenderComponent::TextRenderComponent(Entity* entity, SDL_Renderer& renderer) : RenderComponent(entity), renderer(renderer) {
}

TextRenderComponent::~TextRenderComponent() {
    if(texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void TextRenderComponent::createTexture(SDL_Surface &surface) {
    if(texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    texture = SDL_CreateTextureFromSurface(&renderer, &surface);
    if(texture == nullptr) {
        std::cerr << "Could not create the texture from the specified surface" << std::endl;
    }
}
