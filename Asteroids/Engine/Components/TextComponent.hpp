#pragma once

#include "Engine/Components/Component.hpp"
#include <SDL.h>
#include <string>

class TextComponent : public Component {
public:
    TextComponent(int size, const SDL_Color& color, const std::string& font, const std::string& text);
    ~TextComponent() = default;

    SDL_Color color;
    std::string font = "";
    std::string text = "";
    int size = 0;
};
