#include "Engine/UI/MenuItem.hpp"

MenuItem::MenuItem(int size, std::string text) {
    this->addComponent(new TextComponent(this, size, text));
}
