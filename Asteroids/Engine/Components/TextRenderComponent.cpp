#include "Engine/Components/TextRenderComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"

#include <iostream>

TextRenderComponent::~TextRenderComponent() {
    clean();
}

void TextRenderComponent::clean() {
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

void TextRenderComponent::render(SDL_Renderer& renderer, const TextComponent& textComponent) {
    if(!this->isVisible) {
        return;
    }

    clean();

    font = TTF_OpenFont(textComponent.font.c_str(), textComponent.size);
    if(font == nullptr) {
        std::cerr << "Could not open the specified font" << std::endl;
        return;
    }

    surface = TTF_RenderText_Blended(font, textComponent.text.c_str(), textComponent.color);
    if(surface == nullptr) {
        std::cerr << "Could not create the surface from the specified font" << std::endl;
        return;
    }

    texture = SDL_CreateTextureFromSurface(&renderer, surface);
    if(texture == nullptr) {
        std::cerr << "Could not create the texture from the specified surface" << std::endl;
        return;
    }
    
    TransformComponent* transformComponent = textComponent.getNode<TransformComponent>();
    SDL_Rect rectangle = transformComponent->getRectangle();
    Eigen::Vector2f worldPosition = transformComponent->getWorldPosition();
    rectangle.x = worldPosition.x();
    rectangle.y = worldPosition.y();
        if((rectangle.w == 0 || rectangle.h == 0)) {
            SDL_QueryTexture(texture, nullptr, nullptr, &rectangle.w, &rectangle.h);
            transformComponent->dimensionVector.x() = rectangle.w;
            transformComponent->dimensionVector.y() = rectangle.h;
        }
    
    SDL_RenderCopy(&renderer, texture, nullptr, &rectangle);
}
