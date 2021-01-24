#pragma once

#include "Engine/Components/Component.hpp"
#include <Eigen/Dense>
#include <SDL.h>
#include <vector>

class ShapeComponent : public Component {
public:
    ShapeComponent() = default;
    ShapeComponent(std::initializer_list<Eigen::Vector2f> vertices);
    
    Eigen::Vector2f& operator[](int index);
    
    virtual void addVertex(const Eigen::Vector2f& vertex);
    void clear();
    Eigen::Vector2f getCenter() const;
    unsigned long getSize() const;
    virtual void render(SDL_Renderer& renderer);
protected:
    std::vector<Eigen::Vector2f> vertices;
};
