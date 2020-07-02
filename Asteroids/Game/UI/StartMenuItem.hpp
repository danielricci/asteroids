#pragma once

#include "Engine/UI/MenuItem.hpp"

class StartMenuItem : public MenuItem {
public:
    StartMenuItem();
protected:
    virtual void onEntered() override;
    virtual void onExited() override;
    virtual void onExecute() override;
private:
};
