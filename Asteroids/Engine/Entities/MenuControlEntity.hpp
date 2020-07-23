#pragma once

#include "Engine/Entities/Entity.hpp"
#include <SDL.h>

class MenuControlEntity : public Entity {
public:
    virtual void update(const SDL_Event& event) override final;
    void onExecute(std::function<void()> functor);
private:
    std::function<void()> functor;
};
