#include "Engine/Components/TextComponent.hpp"

TextComponent::TextComponent(Entity* entity, int size, const std::string& text) : Component(entity), size(size), text(text) {
}
