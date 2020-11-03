#pragma once

#include "Engine/System/Node.hpp"
#include <SDL.h>
#include <Eigen/Dense>

class Entity : public Node {
public:
    virtual void update(float deltaTime);
    virtual void update(const SDL_Event& event);
    virtual void render(SDL_Renderer& renderer);
    virtual void setPosition(const Eigen::Vector2f& position) override;
protected:
    Entity();
};
