#pragma once

#include "Engine/System/View.hpp"
#include <SDL.h>
#include <string>

class HomeView : public View {
public:
    HomeView();

    virtual std::string getViewName() const override;
    virtual void update(const SDL_Event& event) override;
    
    virtual void onViewActivated() override;
};
