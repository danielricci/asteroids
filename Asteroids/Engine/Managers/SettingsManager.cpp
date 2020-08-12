#include "Engine/Managers/SettingsManager.hpp"

SettingsManager::SettingsManager(SDL_Window& window) : window(window) {
}

void SettingsManager::getWindowSize(int& width, int& height) const {
    SDL_GetWindowSize(&window, &width, &height);
}
