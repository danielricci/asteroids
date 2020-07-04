#pragma once

#include "Engine/Entities/MenuEntity.hpp"

#include <SDL.h>

class StartMenuEntity : public MenuEntity {
public:
    StartMenuEntity(SDL_Renderer& renderer);
protected:
    virtual void onEntered() override;
    virtual void onExited() override;
    virtual void onExecute() override;
};
