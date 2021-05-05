#pragma once

#include "Engine/Managers/Manager.hpp"
#include "Engine/System/View.hpp"
#include <vector>

class ViewManager : public Manager {
public:
    ViewManager(const std::initializer_list<View*>& views);
    virtual ~ViewManager();
    
    virtual void initialize() override;
private:
    std::vector<View*> views;
};