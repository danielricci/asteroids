#include "Engine/Components/TextComponent.hpp"
#include "Engine/Components/TextRenderComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"

#include <iostream>

TextRenderComponent::TextRenderComponent(Entity* entity, SDL_Renderer& renderer) : RenderComponent(entity), renderer(renderer) {
}

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

void TextRenderComponent::render() {
    if(!this->isVisible) {
        return;
    }
    
    clean();
    
    TextComponent* textComponent = this->getParentEntity()->getComponent<TextComponent>();
    font = TTF_OpenFont(textComponent->font.c_str(), textComponent->size);
    if(font == nullptr) {
        std::cerr << "Could not open the specified font" << std::endl;
        return;
    }
    
    surface = TTF_RenderText_Blended(font, textComponent->text.c_str(), textComponent->color);
    if(surface == nullptr) {
        std::cerr << "Could not create the surface from the specified font" << std::endl;
        return;
    }
    
    texture = SDL_CreateTextureFromSurface(&renderer, surface);
    if(texture == nullptr) {
        std::cerr << "Could not create the texture from the specified surface" << std::endl;
        return;
    }
    TransformComponent* transformComponent = this->getParentEntity()->getComponent<TransformComponent>();
    SDL_Rect rectangle = transformComponent->getRectangle();
    if((rectangle.w == 0 || rectangle.h == 0)) {
        SDL_QueryTexture(texture, nullptr, nullptr, &rectangle.w, &rectangle.h);
        // HACK: Set the transform width and height if the rectangle has
        //       not been specified for a width or a height.
        // NOTE: I do not like the fact that the dimension is set at render time
        //       because it leaves room open for improperly calculated collisions.
        // TODO: Is there is a way to get the dimension earlier at collision detected time?
        transformComponent->dimensionVector.x() = rectangle.w;
        transformComponent->dimensionVector.y() = rectangle.h;
    }
    
    SDL_RenderCopy(&renderer, texture, nullptr, &rectangle);
}
