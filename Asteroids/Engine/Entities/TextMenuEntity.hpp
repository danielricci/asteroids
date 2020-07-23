#pragma once

#include "Engine/Entities/MenuControlEntity.hpp"

#include <SDL.h>
#include <string>

class TextMenuEntity : public MenuControlEntity {
public:
    TextMenuEntity(std::string text, int size);
    virtual void render(SDL_Renderer& renderer) override;
    virtual Eigen::Vector2f getDimension() const override;
protected:
};
