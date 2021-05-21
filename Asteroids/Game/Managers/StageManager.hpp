#pragma once

#include "Engine/Managers/Manager.hpp"

class StageManager : public Manager {
public:
    StageManager() = default;
private:
    int stage = 1;
};
