#pragma once

#include "Engine/Components/Component.hpp"
#include <Eigen/Dense>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class TextComponent : public Component {
public:
    TextComponent(const std::string& fontPath);
    ~TextComponent();

    void setSize(int size);
    void setText(std::string text);
    virtual void render(SDL_Renderer& renderer) override;
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
