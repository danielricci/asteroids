#pragma once

#include "Engine/Entities/MenuEntity.hpp"

#include <SDL.h>
#include <string>

class TextMenuEntity : public MenuEntity {
public:
    virtual void render(SDL_Renderer& renderer) override;
protected:
    TextMenuEntity(std::string text);
    
//    virtual void onEntered();
//    virtual void onExited();
//    virtual void onExecute();
};
