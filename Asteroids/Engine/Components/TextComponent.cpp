#include "Engine/Components/TextComponent.hpp"
#include "Engine/Components/TextRenderComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"

TextComponent::TextComponent(int size, const SDL_Color& color, const std::string& font, const std::string& text) : size(size), color(color), font(font), text(text) {
    this->addComponent(new TransformComponent());
    this->addComponent(new TextRenderComponent());
}
