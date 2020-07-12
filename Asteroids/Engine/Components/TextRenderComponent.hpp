#pragma once

#include "Engine/Components/RenderComponent.hpp"
#include <SDL_ttf.h>
#include <SDL.h>

class TextRenderComponent : public RenderComponent {
public:
    TextRenderComponent() = default;
    ~TextRenderComponent();
      
    void render(SDL_Renderer& renderer);
private:
    void clean();
    
    TTF_Font* font = nullptr;

    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = nullptr;
};
