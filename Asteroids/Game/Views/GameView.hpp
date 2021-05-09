#pragma once

#include "Engine/System/View.hpp"
#include <SDL.h>

class GameView : public View {
public:
    GameView();
    
    virtual void render(SDL_Renderer& renderer) override;
    virtual void update(const SDL_Event& event) override;
};
