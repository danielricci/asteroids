#pragma once

#include "Engine/Entities/Entity.hpp"
#include "Engine/System/Event.hpp"
#include "Engine/System/EventArgs.hpp"
#include <vector>

template <typename T, typename std::enable_if<std::is_base_of<EventArgs, T>::value>::type* = nullptr>
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

    void invoke(Entity* sender, T args = T()) {
        for(int i = (int)functors.size() - 1; i >= 0; --i) {
            functors[i](sender, args);
            if(args.removed) {
                //release(functors[i]);
                args.removed = false;
            }
        }
    }
     
private:
    std::vector<std::function<void(Entity* sender, T& args)>> functors;
};
