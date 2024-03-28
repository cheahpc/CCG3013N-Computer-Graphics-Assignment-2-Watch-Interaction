
const int SYSTEM_POWER_ON_TIME = 25000;             // 25 seconds
const int SYSTEM_POWER_ON_BUTTON_PRESS_TIME = 5000; // 5 seconds
const int SYSTEM_POWER_DOWN_TIME = 5000;              // 5 seconds
const int SYSTEM_POWER_DOWN_BUTTON_PRESS_TIME = 5000; // 5 seconds

struct System
{
    bool poweringUp = false;
    bool poweringDown = false;
    bool isOn = false;
    bool isOff = true;
    bool poweringUpAnimation = false;
    bool poweringDownAnimation = false;

    std::chrono::high_resolution_clock::time_point poweringUpStartTime, poweringDownStartTime;
} System;