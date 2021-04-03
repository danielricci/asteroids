#pragma once

class ManagerInformation {
public:
    enum class State {
        Activate = 0,
        Enabled,
        Destroy,
        Disabled
    };
    
    State state = State::Activate;
};
