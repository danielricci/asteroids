#pragma once

#include "Engine/Components/TextComponent.hpp"
#include "Engine/Components/RenderComponent.hpp"
#include "Engine/Entities/Entity.hpp"
#include <SDL.h>
#include <string>

class MenuControlEntity : public Entity {
public:
    virtual void update(const SDL_Event& event) override final {
        switch(event.type) {
            case SDL_MOUSEBUTTONUP:
                if(functor != nullptr) {
                    (*functor)();
                }
                break;
//            case SDL_MOUSEMOTION:
//            case SDL_MOUSEBUTTONDOWN:
//            case SDL_KEYDOWN:
//            case SDL_KEYUP:
//                break;
        }
        //            SDL_Point point;
        //            point.x = event.motion.x;
        //            point.y = event.motion.y;
        //
        //            SDL_Rect rectangle = mainMenuEntity->getNode<TransformComponent>()->getRectangle();
        //            if(SDL_PointInRect(&point, &rectangle)) {
        //                std::cout << "Mouse Entered" << std::endl;
        //            }
        //SDL_Point point;
        //point.x = event.
    }
    void onExecute(std::function<void()>* functor) {
        this->functor = functor;
    }
    
protected:
    //virtual void onEntered() = 0;
    //virtual void onExited() = 0;
private:
    std::function<void()>* functor = nullptr;
};
