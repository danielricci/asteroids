#include "Engine/Components/TransformComponent.hpp"

SDL_Rect TransformComponent::getRectangle() const {
    SDL_Rect rectangle;
    rectangle.x = positionVector.x();
    rectangle.y = positionVector.y();
    rectangle.w = dimensionVector.x();
    rectangle.h = dimensionVector.y();
    return rectangle;
}

//Eigen::Vector2f TransformComponent::getWorldPosition() const {
//    // Get the parent
//    // for each component in the parent
//    // if its not this transform get its position and then get its parent, put that in a wu
//    Eigen::Vector2f position;
//    Node* parentNode = this->getParentNode();
//    while(parentNode != nullptr) {
//        position += parentNode->getPosition();
//        parentNode = parentNode->getParentNode();
//    }
//    return position;
//}
