#pragma once

#include "Engine/Entities/SoundEntity.hpp"
#include "Engine/Managers/Manager.hpp"
#include <map>
#include <SDL_mixer.h>
#include <string>
#include <vector>

class SoundManager : public Manager {
public:
    SoundManager();
    virtual ~SoundManager();
    
    void allocateSoundChannels(int size);
    int getAllocatedChannelCount() const;
    SoundEntity* getSound(const std::string& name) const;
    void loadSounds(const std::vector<std::string>& names);
    void toggleSound() const;
private:
    std::map<std::string, SoundEntity*> chunks;
    int channels = 0;
};
