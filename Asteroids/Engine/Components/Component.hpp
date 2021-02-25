
#pragma once

#include "Engine/Entities/Entity.hpp"
#include <Eigen/Dense>
#include <SDL.h>
#include <string>

class RenderComponent;
class Entity;

class Component {
public:
    virtual ~Component();

    bool getIsVisible() const;
    virtual void render(SDL_Renderer& renderer);
    std::string getName() const;
    Eigen::Vector2f getPosition() const;
    void setIsVisible(bool isVisible);
    void setName(const std::string& name);
    void setOwnerEntity(Entity* entityOwner);
    void setPosition(const Eigen::Vector2f& position);

protected:
    Component() = default;
    
    virtual RenderComponent* getRenderComponent() const;

    std::string name = "";
    bool isEnabled = true;
    Entity* ownerEntity = nullptr;
    Eigen::Vector2f position;
private:
    RenderComponent* renderComponent = nullptr;
};
