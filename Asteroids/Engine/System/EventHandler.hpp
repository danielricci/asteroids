#pragma once

#include "Engine/Entities/Entity.hpp"
#include <list>

template <typename T> class EventHandler {
public:
    EventHandler() = default;
    virtual ~EventHandler() = default;

    void attach(const std::function<void(Entity* sender, T args)>& functor) {
        functors.push_back(functor);
    }
    void release(const std::function<void(Entity* sender, T args)>& functor) {
        functors.remove(functor);
    }
    void invoke(Entity* sender) {
        for(const auto& functor : functors) {
            functor(sender, T());
        }
    }
private:
    std::list<std::function<void(Entity* sender, T args)>> functors;
};
