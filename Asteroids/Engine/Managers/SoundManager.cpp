#include "Engine/Managers/SoundManager.hpp"
#include <algorithm>
#include <iostream>
#include <SDL.h>

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
    std::for_each(chunks.begin(), chunks.end(), [this](auto& thisPair) {
        if(thisPair.second != nullptr) {
            delete thisPair.second;
            thisPair.second = nullptr;
        }
    });
    chunks.clear();
    Mix_Quit();
}

SoundEntity* SoundManager::getSound(const std::string& name) const {
    return chunks.at(name);
}

void SoundManager::loadSound(const std::string& path) {
    if(path.size() > WAV_EXTENSION.size() && path.compare(path.size() - WAV_EXTENSION.size(), WAV_EXTENSION.size(), WAV_EXTENSION) == 0) {
        std::string filename = path.substr(path.find_last_of("/\\") + 1);
        std::string::size_type const p(filename.find_last_of('.'));
        chunks.insert_or_assign(filename.substr(0, p), new SoundEntity(path));
    }
}

void SoundManager::allocateSoundChannels(int size) {
    int allocatedChannels = Mix_AllocateChannels(size);
    if(allocatedChannels > -1) {
        channels = allocatedChannels;
    }
}

int SoundManager::getAllocatedChannelCount() const {
    return channels;
}

void SoundManager::toggleSound() const {
    Mix_Volume(-1, Mix_Volume(-1, -1) != 0 ? 0 : MIX_MAX_VOLUME);
}
