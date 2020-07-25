#include "Engine/Core/Clock.hpp"
#include <SDL.h>

float Clock::sample() {
    if(nowTime == 0) {
        nowTime = SDL_GetPerformanceCounter();
    }
    lastTime = nowTime;
    nowTime = SDL_GetPerformanceCounter();
    return (nowTime - lastTime) / static_cast<float>(SDL_GetPerformanceFrequency());
}
