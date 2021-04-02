#pragma once

#include "Engine/Entities/Entity.hpp"
#include "Engine/System/Event.hpp"
#include <list>

template <typename T>
class Event {
public:
    Event() = default;
    virtual ~Event() {
        functors.clear();
    }

    void attach(const std::function<void(Entity* sender, T args)>& functor) {
        functors.push_back(functor);
    }

    void release(const std::function<void(Entity* sender, T args)>& functor) {
        functors.remove(functor);
    }

    void invoke(Entity* sender, T t = T()) {
        for(const auto& functor : functors) {
            functor(sender, t);
        }
    }
    
private:
    std::list<std::function<void(Entity* sender, T args)>> functors;
};
