#pragma once

#include "Engine/Managers/Manager.hpp"

class StageManager : public Manager {
public:
    StageManager();
    void nextStage();
    void reset();
private:
    int stage = 1;
};
