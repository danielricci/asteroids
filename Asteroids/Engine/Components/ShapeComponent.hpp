#pragma once

#include "Engine/Components/Component.hpp"
#include <Eigen/Dense>
#include <SDL.h>
#include <vector>

class ShapeComponent : public Component {
public:
    ShapeComponent() = default;
    ShapeComponent(const std::initializer_list<Eigen::Vector2f>& vertices);
    ShapeComponent(const std::vector<Eigen::Vector2f>& vertices);
    
    Eigen::Vector2f& operator[](int index);
    
    virtual void addVertex(const Eigen::Vector2f& vertex);
    void clear();
    std::vector<std::pair<Eigen::Vector2f, Eigen::Vector2f>> getEdges() const;
    SDL_FRect getRectangle() const;
    unsigned long getSize() const;
    virtual void render(SDL_Renderer& renderer) override;    
protected:
    std::vector<Eigen::Vector2f> vertices;
private:
    std::vector<std::pair<Eigen::Vector2f, Eigen::Vector2f>> edges;
};
