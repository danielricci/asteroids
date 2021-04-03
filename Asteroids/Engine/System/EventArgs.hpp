#pragma once

class EventArgs {
public:
    static EventArgs Empty() {
        return EventArgs();
    }
    
    bool removed = false;
};
