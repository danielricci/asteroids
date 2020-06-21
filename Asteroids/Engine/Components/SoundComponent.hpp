#pragma once

#include "Engine/Components/Component.hpp"

#include <SDL_mixer.h>

#include <string>

class SoundComponent : public Component {
public:
    SoundComponent(Entity* entity, const std::string& path);
    ~SoundComponent();
    
    void play(int loops = 0) const;
private:
    Mix_Chunk* chunk { nullptr };
    const std::string& path;
};
