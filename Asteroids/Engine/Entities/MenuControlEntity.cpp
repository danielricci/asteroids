#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Entities/MenuControlEntity.hpp"

void MenuControlEntity::update(const SDL_Event& event) {
    switch(event.type) {
        //case SDL_MOUSEMOTION:
        //case SDL_MOUSEBUTTONDOWN:
        //case SDL_KEYDOWN:
        //case SDL_KEYUP:
//        case SDL_MOUSEBUTTONUP: {
//            if(functor != nullptr) {
//                SDL_Point point;
//                point.x = event.motion.x;
//                point.y = event.motion.y;
//                SDL_Rect rectangle = TransformComponent::toRectangle(this->getWorldPosition(), this->getDimension());
//                if(SDL_PointInRect(&point, &rectangle)) {
//                    this->functor();
//                }
//            }
//            break;
//        }
    }
}

void MenuControlEntity::onExecute(std::function<void ()> functor) {
    //this->functor = functor;
}
