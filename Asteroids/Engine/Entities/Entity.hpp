#pragma once

#include "Engine/Components/Component.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/System/Node.hpp"
#include <Eigen/Dense>
#include <SDL.h>
#include <list>

class Entity : public Node {
public:
    virtual Eigen::Vector2f getPosition() const override;    
    virtual void update(const SDL_Event& event);
    virtual void render(SDL_Renderer& renderer);
protected:
    Entity();
};
