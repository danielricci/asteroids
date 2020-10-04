#include "Engine/Managers/SoundManager.hpp"
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>

SoundManager::SoundManager() {
    if(SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL audio initialization failed: " << SDL_GetError() << std::endl;
        return;
    }
    
    if(Mix_OpenAudio(11025, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
        std::cerr << "SDL_mixer could not be initilized: " << Mix_GetError() << std::endl;
        return;
    }

    Mix_Volume(-1, MIX_MAX_VOLUME);
}

SoundManager::~SoundManager() {
    Mix_Quit();
}

void SoundManager::toggleSound() const {
    Mix_Volume(-1, Mix_Volume(-1, -1) != 0 ? 0 : MIX_MAX_VOLUME);
}

void SoundManager::allocateSoundChannels(int size) {
    int allocatedChannels = Mix_AllocateChannels(size);
    if(allocatedChannels > -1) {
        soundChannelsCount = allocatedChannels;
    }
}

int SoundManager::getAllocatedChannelCount() const {
    return soundChannelsCount;
}
