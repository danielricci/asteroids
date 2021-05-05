#pragma once

#include "Engine/Entities/Entity.hpp"
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

class SoundEntity : public Entity {
public:
    SoundEntity(const std::string& path);
    virtual ~SoundEntity();

    void play(int loops = 0);
    void stop();
    
    static const int INFINITE_LOOP = -1;
private:
    bool isPlaying() const;
    
    static const int NO_CHANNEL = INT_MIN;
    int channel = NO_CHANNEL;
    Mix_Chunk* chunk = nullptr;
    const std::string& path;
};
