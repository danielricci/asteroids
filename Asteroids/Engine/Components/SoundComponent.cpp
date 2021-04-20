#include "Engine/Components/SoundComponent.hpp"
#include <iostream>

SoundComponent::SoundComponent(const std::string& path) : path(path) {
    chunk = Mix_LoadWAV(path.c_str());
    if(chunk == nullptr) {
        std::cerr << "Mix_LoadWav: Could not load sound " << path << ": " << Mix_GetError() << std::endl;
    }
}

SoundComponent::~SoundComponent() {
    if(chunk != nullptr) {
        Mix_FreeChunk(chunk);
        chunk = nullptr;
    }
}

bool SoundComponent::isPlaying() const {
    return this->channel != NO_CHANNEL && Mix_Playing(this->channel);
}

void SoundComponent::stop() {
    if(this->channel != NO_CHANNEL) {
        Mix_HaltChannel(this->channel);
        this->channel = NO_CHANNEL;
    }
}

void SoundComponent::play(int loops) {
    if(chunk != nullptr) {
        if(this->isPlaying()) {
            return;
        }
        
        int mixChannel = Mix_PlayChannel(-1, chunk, loops);
        if(mixChannel == -1) {
            std::cerr << "Mix_PlayChannel: " << Mix_GetError() << std::endl;
        }
        else {
            this->channel = mixChannel;
        }
    }
    else {
        std::cerr << "Could not play sound " << path << ", invalid chunk" << std::endl;
    }
}
