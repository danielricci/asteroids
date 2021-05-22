#pragma once

#include "Engine/Managers/Manager.hpp"

class StageManager : public Manager {
public:
    StageManager() = default;
    void nextStage();
    void reset();
private:
    int stage = 0;
};
