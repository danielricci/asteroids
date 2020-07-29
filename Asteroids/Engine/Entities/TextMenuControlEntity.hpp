#pragma once

#include "Engine/Entities/MenuControlEntity.hpp"
#include <SDL.h>
#include <string>

class TextMenuControlEntity : public MenuControlEntity {
public:
    TextMenuControlEntity(std::string text, int size);
    virtual void render(SDL_Renderer& renderer) override;
    virtual Eigen::Vector2f getDimension() const override;
};
