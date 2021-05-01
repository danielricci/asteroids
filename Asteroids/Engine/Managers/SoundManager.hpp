#pragma once

#include "Engine/Entities/SoundEntity.hpp"
#include "Engine/Managers/Manager.hpp"
#include <map>
#include <string>

class SoundManager : public Manager {
public:
    SoundManager();
    virtual ~SoundManager();
    
    void allocateSoundChannels(int size);
    int getAllocatedChannelCount() const;
    SoundEntity* getSound(const std::string& name) const;
    void toggleSound() const;
private:
    void loadSound(const std::string& name);
    
    const std::string WAV_EXTENSION = ".wav";
    std::map<std::string, SoundEntity*> chunks;
};
