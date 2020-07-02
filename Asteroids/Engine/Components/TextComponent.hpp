#pragma once

#include "Engine/Components/Component.hpp"
#include <SDL.h>
#include <string>

class TextComponent : public Component {
public:
    TextComponent(Entity* entity, int size, const std::string& text);
    ~TextComponent() = default;

    const SDL_Color color { 255, 255, 255 };
    const std::string font = "Resources/Fonts/Verdana.ttf";
    const std::string text = "";
    const int size = 0;
};
