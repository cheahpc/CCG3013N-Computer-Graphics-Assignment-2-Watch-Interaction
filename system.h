
const int SYSTEM_BOOT_TIME = 25000;                 // 25 seconds
const int SYSTEM_BOOT_BUTTON_PRESS_TIME = 5000;     // 5 seconds
const int SYSTEM_SHUTDOWN_TIME = 5000;              // 5 seconds
const int SYSTEM_SHUTDOWN_BUTTON_PRESS_TIME = 5000; // 5 seconds

std::chrono::high_resolution_clock::time_point buttonPressStartTime, bootStartTime, shutdownStartTime;

bool watchButtonPressed = false;           // button press toggle
bool bootingUp = false;                    // booting animation toggle
bool bootingUpAnimationToggled = false;    // booting animation toggle
bool systemRunning = false;                // system running toggle
bool shuttingDown = false;                 // shutting down animation toggle
bool shuttingDownAnimationToggled = false; // shutting down animation toggle