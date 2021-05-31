#pragma once

#include "Engine/System/View.hpp"
#include <SDL.h>
#include <string>

class GameView : public View {
public:
    GameView();
    
    virtual std::string getViewName() const override;

    virtual void onViewActivated() override;
    virtual void render(SDL_Renderer& renderer) override;
    virtual void update(float deltaTime) override;
    virtual void update(const SDL_Event& event) override;
private:
    float spawnTimerSaucer = 0.f;
    const int SPAWN_SAUCER_TIMER = 10;
};
