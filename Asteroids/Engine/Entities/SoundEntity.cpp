#include "Engine/Entities/SoundEntity.hpp"
#include <iostream>

SoundEntity::SoundEntity(const std::string& path) : path(path) {
    chunk = Mix_LoadWAV(("Resources/" + path).c_str());
    if(chunk == nullptr) {
        std::cerr << "Mix_LoadWav: Could not load sound " << path << ": " << Mix_GetError() << std::endl;
    }
}

SoundEntity::~SoundEntity() {
    if(chunk != nullptr) {
        Mix_FreeChunk(chunk);
        chunk = nullptr;
    }
}

bool SoundEntity::isPlaying() const {
    return this->channel != NO_CHANNEL && Mix_Playing(this->channel);
}

void SoundEntity::stop() {
    if(this->channel != NO_CHANNEL) {
        Mix_HaltChannel(this->channel);
        this->channel = NO_CHANNEL;
    }
}

void SoundEntity::play(int loops) {
    if(chunk != nullptr) {
        if(this->isPlaying()) {
            //return;
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
