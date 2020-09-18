#include "Engine/Managers/GameSettingsManager.hpp"

GameSettingsManager::GameSettingsManager(SDL_Window& window) : window(window) {
}

void GameSettingsManager::getWindowSize(int& width, int& height) const {
    SDL_GetWindowSize(&window, &width, &height);
}
