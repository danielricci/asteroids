#pragma once

#include "Engine/Managers/Manager.hpp"
#include "Engine/System/View.hpp"
#include <SDL.h>
#include <string>

class ViewManager : public Manager {
public:
    ViewManager(const std::initializer_list<View*>& views);
    virtual ~ViewManager();
    
    virtual void render(SDL_Renderer& renderer) override;
    void setActiveView(const std::string& viewName);
    virtual void update(float deltaTime) override;
    virtual void update(const SDL_Event& event) override;
private:
    View* activeView = nullptr;
};
