#pragma once

#include "Engine/Managers/Manager.hpp"

class SoundManager : public Manager {
public:
    SoundManager();
    ~SoundManager();
    void toggleSound() const;
    void allocateSoundChannels(int size);
    int getAllocatedChannelCount() const;
private:
    int soundChannelsCount = 0;
};