#pragma once

class Clock {
public:
    float sample();
private:
    long long int lastTime = 0;
    long long int nowTime = 0;
};
