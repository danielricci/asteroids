#pragma once

#include "Engine/Components/Component.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class TextComponent : public Component {
public:
    TextComponent(const std::string& fontPath);
    TextComponent(const std::string& fontPath, const std::string& text, int size);
    ~TextComponent();

    virtual void render(SDL_Renderer& renderer) override;
    void setSize(int size);
    void setText(std::string text);
private:
    void clean();

    bool isDirty = false;
    std::string fontPath = "";
    std::string text = "";
    int size = 12;
    SDL_Color color {255, 255, 255};
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = nullptr;
    TTF_Font* font = nullptr;
};
