#pragma once

#include "Engine/Entities/Entity.hpp"
#include <vector>
#include <SDL.h>

class View : public Entity {
public:
    virtual ~View();

    virtual void onViewActivated();
    virtual void render(SDL_Renderer& renderer) override;
    virtual void update(float deltaTime) override;
    virtual void update(const SDL_Event& event) override;
protected:
    std::vector<Entity*> entities;
    static std::vector<Entity*> shared_entities;
    
    template<typename T> T* getEntity(bool isSharedEntity = false) const {
        T* entityResult = nullptr;
        for(Entity* entity : isSharedEntity ? shared_entities : this->entities) {
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
