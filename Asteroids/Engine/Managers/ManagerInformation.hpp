#pragma once

class ManagerInformation {
public:
    enum class State {
        Active,
        Inactive,
        Destroy
    };
    
    State state = State::Active;
};
