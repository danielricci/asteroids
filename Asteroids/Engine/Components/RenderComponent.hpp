#pragma once

#include "Engine/Components/Component.hpp"

class RenderComponent : public Component {
public:
    RenderComponent() = default;
    bool isVisible { true };
};
