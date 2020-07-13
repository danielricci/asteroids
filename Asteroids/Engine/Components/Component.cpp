#include "Engine/Components/Component.hpp"

void Component::setOffsetPosition(float x, float y) {
    offsetPosition.x() = x;
    offsetPosition.y() = y;
}
