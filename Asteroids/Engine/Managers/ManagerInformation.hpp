#pragma once

class ManagerInformation {
public:
    enum class State {
        Activate = 0,
        Destroy,
    };
    
    State state = State::Activate;
};
