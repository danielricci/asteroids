#pragma once

#include "Engine/Components/Component.hpp"
#include <Eigen/Dense>
#include <random>
#include <SDL.h>

class TransformComponent final : public Component {
public:
    TransformComponent() {
        setIsVisible(false);
    }
    
    static float toRadians(float degrees) {
        return degrees * M_PI/180;
    }
    
    static int getRandomRotation() {
        // TODO - spend more time on this, look also at https://stackoverflow.com/questions/39288595/why-not-just-use-random-device
        std::uniform_int_distribution<unsigned int> rotationDistribution(TransformComponent::ROTATION_RIGHT, std::abs(TransformComponent::ROTATION_FULL_UNIT));
        std::mt19937 generator(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
        return -rotationDistribution(generator);
    }
    
    virtual void render(SDL_Renderer& renderer) override {
        if(!getIsVisible()) {
            return;
        }
        
        SDL_Color color;
        SDL_GetRenderDrawColor(&renderer, &color.r, &color.g, &color.b, &color.a);

        Eigen::Vector2f position = ownerEntity->getPosition();
        Eigen::Vector2f xPoint2 = ownerEntity->getPosition({30, 0});
        SDL_SetRenderDrawColor(&renderer, 0xFF, 0x00, 0x00, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(&renderer, position.x(), position.y(), xPoint2.x(), xPoint2.y());
        Eigen::Vector2f yPoint2 = ownerEntity->getPosition({0, 30});
        SDL_SetRenderDrawColor(&renderer, 0x00, 0xFF, 0x00, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(&renderer, position.x(), position.y(), yPoint2.x(), yPoint2.y());

        SDL_SetRenderDrawColor(&renderer, color.r, color.g, color.b, color.a);
    }
       
    static const int ROTATION_RIGHT = 0;
    static const int ROTATION_TOP_RIGHT = -45;
    static const int ROTATION_TOP = -90;
    static const int ROTATION_LEFT = -180;
    static const int ROTATION_DOWN = -270;
    static const int ROTATION_FULL_UNIT = -360;
    
    int orientation = 0;
    Eigen::Vector2f position { 0, 0 };
    Eigen::Vector2f dimensions { 0, 0 };
};
