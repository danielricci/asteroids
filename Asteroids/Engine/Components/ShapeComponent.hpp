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
    const Eigen::Vector2f& operator[](int index) const;
    
    virtual void addVertex(const Eigen::Vector2f& vertex);
    void clear();
    SDL_FRect getRectangle() const;
    unsigned long getSize() const;
    virtual void render(SDL_Renderer& renderer) override;
    void setColor(const SDL_Color& color);
protected:
    std::vector<Eigen::Vector2f> vertices;
private:
    SDL_Color color = {255, 255, 255};
};
