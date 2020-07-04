#include "Game/Entities/StartMenuEntity.hpp"

MenuEntity::MenuEntity(int size, std::string text) {
    this->addComponent(new TextComponent(this, size, text));
}
