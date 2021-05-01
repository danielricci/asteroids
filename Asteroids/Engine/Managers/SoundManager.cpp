#include "Engine/Managers/SoundManager.hpp"
#include <algorithm>
#include <filesystem>
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

    for(const auto& entry : std::filesystem::directory_iterator(std::string(std::filesystem::current_path()) + "/Resources")) {
        loadSound(entry.path());
    }
    std::cout << "[Sound] - Resources Loaded: " << chunks.size() << std::endl;
    
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
        std::cout << "[Sound] - Loading Resource: " << path << std::endl;
        std::string filename = path.substr(path.find_last_of("/\\") + 1);
        std::string::size_type const p(filename.find_last_of('.'));
        chunks.insert_or_assign(filename.substr(0, p), new SoundEntity(path));
    }
}

void SoundManager::toggleSound() const {
    Mix_Volume(-1, Mix_Volume(-1, -1) != 0 ? 0 : MIX_MAX_VOLUME);
}
