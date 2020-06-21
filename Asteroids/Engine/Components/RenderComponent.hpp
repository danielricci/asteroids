#pragma once

#include "Engine/Components/Component.hpp"

class RenderComponent : public Component {
public:
    RenderComponent(Entity* entity) : Component(entity) {
    }
    
    bool isVisible { true };
};
