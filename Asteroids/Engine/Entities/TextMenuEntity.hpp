#pragma once

#include "Engine/Entities/MenuControlEntity.hpp"

#include <SDL.h>
#include <string>

class TextMenuEntity : public MenuControlEntity {
public:
    TextMenuEntity(std::string text, int size);
    virtual void render(SDL_Renderer& renderer) override;
    //virtual void onExecute2(std::function<void()> functor) override;
protected:
//    virtual void onEntered() override;
//    virtual void onExited() override;
//    virtual void onExecute() override;
};
