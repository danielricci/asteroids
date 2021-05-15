#pragma once

#include "Engine/System/View.hpp"
#include <SDL.h>
#include <string>

class GameView : public View {
public:
    GameView();
    
    virtual std::string getViewName() const override;
    
    virtual void render(SDL_Renderer& renderer) override;
    virtual void update(const SDL_Event& event) override;
};
