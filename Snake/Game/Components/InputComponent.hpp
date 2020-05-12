/**
* MIT License
*
* Copyright (c) 2020 Daniel Ricci {@literal <thedanny09@icloud.com>}
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#pragma once

#include "Game/Components/Component.hpp"

#include <SDL.h>

#include <unordered_map>
#include <string>

class InputComponent : public Component {

public:
    InputComponent(GameObject* gameObject) : Component(gameObject) {
    }
    
    void addBinding(SDL_Keycode keyCode, const std::string& action) {
        inputBindings.emplace(keyCode, action);
    }

    void addBinding(SDL_Keycode keyCode, const std::string& action, std::function<void(const SDL_Event&)> functor) {
        addBinding(keyCode, action);
        registerActionBinding(action, functor);
    }
    
    void addBinding(SDL_GameControllerAxis axis, const std::string& action) {
        inputBindings.emplace(axis, action);
    }

    void addBinding(SDL_GameControllerAxis axis, const std::string& action, std::function<void(const SDL_Event&)> functor) {
        addBinding(axis, action);
        registerActionBinding(action, functor);
    }
    
    void handleEvent(const SDL_Event& event) {
        InputBindingsMap::const_iterator inputIterator = inputBindings.find(event.key.keysym.sym);
        if(inputIterator == inputBindings.end()) {
            inputIterator = inputBindings.find(event.caxis.axis);
        }
        
        if(inputIterator != inputBindings.end()) {
            ActionBindingsMap::const_iterator actionIterator = actionBindings.find(inputIterator->second);
            if(actionIterator != actionBindings.end()) {
                actionIterator->second(event);
            }
        }
    }

    void registerActionBinding(const std::string& action, std::function<void(const SDL_Event&)> functor) {
        actionBindings[action] = functor;
    }
    
protected:
    virtual int getDeadZone() const {
        return 8000;
    }
    
private:
    typedef std::unordered_multimap<SDL_Keycode, std::string> InputBindingsMap;
    InputBindingsMap inputBindings;
    
    typedef std::unordered_map<std::string, std::function<void(const SDL_Event&)>> ActionBindingsMap;
    ActionBindingsMap actionBindings;
};
