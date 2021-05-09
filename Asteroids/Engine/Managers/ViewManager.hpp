#pragma once

#include "Engine/Managers/Manager.hpp"
#include "Engine/System/View.hpp"
#include <SDL.h>

class ViewManager : public Manager {
public:
    ViewManager(const std::initializer_list<View*>& views);
    virtual ~ViewManager();
    
    virtual void update(const SDL_Event& event) override;
};
