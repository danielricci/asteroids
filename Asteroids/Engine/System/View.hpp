#pragma once

#include "Engine/Entities/Entity.hpp"
#include <vector>
#include <SDL.h>

class View : public Entity {
public:
    virtual ~View();

    virtual void onViewActivated();
    virtual void render(SDL_Renderer& renderer) override;
protected:
    std::vector<Entity*> entities;
    
    template<typename T> T* getEntity() const {
        T* entityResult = nullptr;
        for(Entity* entity : this->entities) {
            T* cast = dynamic_cast<T*>(entity);
            if(cast != nullptr) {
                entityResult = cast;
                break;
            }
        }
        return entityResult;
    }
public:
    virtual std::string getViewName() const = 0;
};
