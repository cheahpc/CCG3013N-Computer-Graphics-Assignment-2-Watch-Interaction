const int SYS_P_ON_TIME = 25000;             // 25 seconds
const int SYS_P_ON_OFF_BTN_HOLD_TIME = 5000; // 5 seconds
const int SYS_P_OFF_TIME = 5000;

enum class AnimState
{
    IDLE,
    ANIMATING,
    DONE
};

enum class SystemState
{
    OFF,
    ON,
    POWERING_ON,
    POWERING_OFF_TRIGGERED,
    POWERING_OFF_CANCELLED,
    POWERING_OFF
};

enum class ScreenState
{
    NONE,
    MAIN,
    POWERING_ON,
    POWER_OFF_CONFIRMATION,
    POWERING_OFF,
    STOPWATCH,
    TIMER
};

enum class PowerOffConfirmationState
{
    NONE,
    YES,
    NO
};

enum class StopwatchState
{
    IDLE,
    RUNNING,
    PAUSED
} stopwatchState;

enum class TimerState
{
    IDLE,
    RUNNING,
    PAUSED
} timerState;

enum class TimerSelectorState
{
    HOUR,
    MINUTE,
    SECOND,
    NONE
} timerSelectorState;

struct System
{
    bool is24HrFormat = false;
    SystemState state = SystemState::OFF;
    ScreenState currentScreen = ScreenState::NONE;
    float batteryLevel = 15.0;
    float chargingRate = 0.2;
    float depletedRate = 0.7;
    float minimumBatteryLevel = 10.0;
    bool isCharging = false;
} System;

struct Debug_Object
{
    Object grid = Object(0, 0, 1, 0, COLOR_BLACK, 0);
    Object test = Object(0, 0, 1, 0, COLOR_RED, 80);
} ObjDebug;

struct Backdrop_Object
{
    Object bg = Object(0, 0, 1, 0, COLOR_WHITE, 100);
} ObjBackdrop;

struct Watch_Object
{
    Object strap = Object(0, 0, 1, 0, COLOR_THEME_GREEN_DARK_1, 100);
    Object body = Object(0, 0, 1, 0, COLOR_BLACK_4, 100);
    Object dial = Object(WATCH_DIAL_CENTER_X, WATCH_DIAL_CENTER_Y, 1, 0, COLOR_GOLD, 100);
    struct Button
    {
        Object obj = Object(WATCH_BUTTON_CENTER_X, WATCH_BUTTON_CENTER_Y, 1, 0, COLOR_GOLD, 100);
        bool isDown = false;

        chrono::high_resolution_clock::time_point downStartTime;
    } Button;
} ObjWatch;

struct UI_Object
{
    // BG
    Object bg = Object(0, 0, 1, 0, COLOR_BLACK_1, 100);
    Object legend = Object(0, 0, 1, 0, COLOR_BLACK, 100);

    // Complication Area
    Object complication1 = Object(COMPLICATION_X_POS, COMPLICATION_Y_POS_1, 0, 0, COLOR_THEME_GREEN_DARK_2, 0);
    Object complication2 = Object(COMPLICATION_X_POS, COMPLICATION_Y_POS_1, 0, 0, COLOR_THEME_GREEN_DARK_2, 0);
    Object complication3 = Object(COMPLICATION_X_POS, COMPLICATION_Y_POS_1, 0, 0, COLOR_THEME_GREEN_DARK_2, 0);
    Object complication4 = Object(COMPLICATION_X_POS, COMPLICATION_Y_POS_1, 0, 0, COLOR_THEME_GREEN_DARK_2, 0);

    Object comp1Battery = Object(COMPLICATION_X_POS, COMPLICATION_Y_POS_1, 1, 0, COLOR_WHITE, 0);
    Object comp1BatteryText = Object(COMP1_BATTERY_TEXT_X_POS, COMP1_BATTERY_TEXT_Y_POS, 0.13, 0, COLOR_WHITE, 100);
    Object comp2Stopwatch = Object(COMPLICATION_X_POS, COMPLICATION_Y_POS_2, 1, 0, COLOR_WHITE, 0);
    Object comp3Timer = Object(COMPLICATION_X_POS, COMPLICATION_Y_POS_3, 1, 0, COLOR_WHITE, 0);
    Object comp4Text = Object(COMP4_TEXT_X_POS, COMP4_TEXT_Y_POS, 0.2, 0, COLOR_WHITE, 0);

    // DateTime Area
    Object time = Object(-90, 70, 0.5, 0, COLOR_WHITE, 0);
    Object dateBox = Object(43, 20, 0.5, 0, COLOR_THEME_GREEN_LIGHT_1, 0);
    Object date = Object(-70, 10, 0.2, 0, COLOR_THEME_GREEN_DARK_3, 0);

    // Heart Rate Area
    Object heartIcon = Object(50, 170, 1, 0, COLOR_RED, 0);
    Object heartRate = Object(-20, 100, 0.2, 0, COLOR_WHITE, 0);

    // Step Counter Area
    Object stepCountText = Object(25, -150, 0.4, 0, COLOR_WHITE, 0);
    Object stepStepText = Object(-5, -200, 0.2, 0, COLOR_WHITE, 0);

    // Battery Level Area
    bool isBatteryPercentageVisible = false;

    // Heart Rate variables
    float heartRateInterval = 0;
    float heartRateValue = 0;
    bool isHeartBeating = false;
    bool isHeartBeatUp = true;
    int heartBeatOffset = 0;

    // Step variables
    int stepCount = 0;
    int stepLastSampleCount = 0;
    bool lastStepIsLeft = false;
    float stepSamplePeriod = 5000;

    chrono::high_resolution_clock::time_point animStartTime, heartRateLastSampleTime, stepLastSampleTime;

    AnimState animState = AnimState::IDLE;

} ObjUI;

struct Stopwatch_Object
{
    Object bg = Object(0, 0, 1, 0, COLOR_BLACK_1, 0);
    Object stopwatchIcon = Object(0, 180, 1, 0, COLOR_WHITE, 0);
    Object stopwatchLabel = Object(-133, 90, 0.3, 0, COLOR_WHITE, 0);
    Object elapsedTimeText = Object(-183, -30, 0.7, 0, COLOR_WHITE, 0);
    Object elapsedTimeMilliText = Object(-158, -180, 1, 0, COLOR_WHITE, 0);

    StopwatchState stopwatchState = StopwatchState::IDLE;

    string elapsedMinSec = "00:00";
    string elapsedMilli = "000";

    chrono::high_resolution_clock::time_point animStartTime, stopwatchStartTime, stopwatchPauseTime, stopwatchElapsedTime;
    AnimState animState = AnimState::IDLE;
} ObjStopwatch;

struct Timer_Object
{
    Object bg = Object(0, 0, 1, 0, COLOR_BLACK_1, 0);
    Object timerIcon = Object(0, 180, 1, 0, COLOR_WHITE, 0);
    Object timerLabel = Object(-80, 90, 0.3, 0, COLOR_WHITE, 0);
    Object timerText = Object(-168, -30, 0.4, 0, COLOR_WHITE, 0);
    Object selector = Object(0, -10, 1, 0, COLOR_THEME_GREEN, 0);
    Object divider = Object(0, -100, 1, 0, COLOR_WHITE, 0);
    Object startBtnText = Object(-130, -200, 0.5, 0, COLOR_WHITE, 0);

    Object notiBg = Object(0, 0, 1, 0, COLOR_BLACK, 0);
    Object notiTitle = Object(-140, 180, 0.3, 0, COLOR_WHITE, 0);
    Object notiMessage = Object(-140, 80, 0.2, 0, COLOR_WHITE, 0);
    Object notiDivider = Object(0, 10, 1, 0, COLOR_WHITE, 0);
    Object notiOkText = Object(60, -50, 0.2, 0, COLOR_WHITE, 0);

    string timerHourMinSec = "00:00:00";
    int timerHour = 0, timerMinute = 0, timerSecond = 0;
    int initialHour = 0, initialMinute = 0, initialSecond = 0;
    int totalTimerDuration;

    bool isDragging = false;
    bool isTimesUp = false;

    TimerState timerState = TimerState::IDLE;
    TimerSelectorState timerSelectorState = TimerSelectorState::SECOND;

    chrono::high_resolution_clock::time_point animStartTime, timerStartTime, timerPauseTime, timerElapsedTime;
    AnimState animState = AnimState::IDLE;
} ObjTimer;

struct Help_Object
{
    Object bg = Object(-650, 0, 1, 0, COLOR_THEME_GREEN_DARK_2, 0);
    Object hintText = Object(-780, 160, 0.25, 0, COLOR_THEME_GREEN_DARK_1, 100);
    Object helpText = Object(0, 0, 0.18, 0, COLOR_WHITE, 0);

    bool isHelpVisible = false;
} ObjHelp;

struct Powering_On_Object
{
    Object bg = Object(0, 0, 1, 0, COLOR_BLACK_1, 0);
    Object logo = Object(-170, -100, 0.55, 0, COLOR_THEME_GREEN, 0);
    Object indicator = Object((-UI_SCREEN_WIDTH / 2) + 40, (UI_SCREEN_HEIGHT / 2) - 40, 1, 0, COLOR_THEME_GREEN_LIGHT_1, 0);
    Object loadingText = Object(-130, -50, 0.20, 0, COLOR_WHITE, 100);
    Object loadingRing = Object(0, 0, 1, 0, COLOR_THEME_GREEN, 100);
    Object loadingRing_Null = Object(0, 0);

    AnimState pOnAnimState = AnimState::IDLE;
    std::chrono::high_resolution_clock::time_point pOnStartTime;
} ObjPowerOn;

struct Powering_Off_Object
{
    // For confirmation
    Object bgBlur = Object(0, 0, 1, 0, COLOR_BLACK, 0);
    Object bg = Object(0, 80, 1, 0, COLOR_BLACK_1, 0);
    Object title = Object(-140, 180, 0.3, 0, COLOR_WHITE, 0);
    Object message = Object(-140, 80, 0.2, 0, COLOR_WHITE, 0);
    Object yesText = Object(60, -50, 0.2, 0, COLOR_RED, 0);
    Object noText = Object(-115, -50, 0.2, 0, COLOR_WHITE, 0);
    Object dividerLineHorizontal = Object(0, 10, 1, 0, COLOR_WHITE, 0);
    Object dividerLineVertical = Object(0, -40, 1, 0, COLOR_WHITE, 0);

    // For power off
    Object offBg = Object(0, 0, 1, 0, COLOR_BLACK_1, 0);
    Object offRing = Object(0, 0, 1, 0, COLOR_THEME_GREEN, 0);
    Object offRing_Null = Object(360, 0, 1, 0, COLOR_TRANSPARENT, 0);
    Object offLogo = Object(-170, 20, 0.55, 0, COLOR_THEME_GREEN, 0);
    Object offText = Object(-90, -50, 0.20, 0, COLOR_WHITE, 0);
    Object offIndicator = Object((-UI_SCREEN_WIDTH / 2) + 40, (UI_SCREEN_HEIGHT / 2) - 40, 1, 0, COLOR_RED, 0);

    AnimState pOffAnimState = AnimState::IDLE;
    AnimState pOffOverlayAnimState = AnimState::IDLE;
    PowerOffConfirmationState pOffConfirmation = PowerOffConfirmationState::NONE;
    chrono::high_resolution_clock::time_point pOffStartTime, pOffOverlayStartTime;
} ObjPowerOff;

struct Charging_Object
{
    Object bg = Object(0, 0, 1, 0, COLOR_BLACK_1, 0);
    Object battery = Object(0, 20, 1, 0, COLOR_WHITE, 0);
    Object chargingText = Object(0, 0, 0.4, 0, COLOR_WHITE, 0);

    Object dock = Object(WINDOWS_WIDTH / 2, -WINDOWS_HEIGHT / 2, 1, 0, COLOR_THEME_GREEN_DARK_2, 100);
    Object dockWire = Object(WINDOWS_WIDTH / 2, -WINDOWS_HEIGHT / 2, 1, 0, COLOR_BLACK_1, 100);
    Object dockLabel = Object(0, 0, 0.3, 0, COLOR_THEME_GREEN, 100);

    bool isDragging = false;
    int dockInitialX, dockInitialY;

    AnimState chargingAnimState = AnimState::IDLE;
    chrono::high_resolution_clock::time_point chargingAnimStartTime;
} ObjCharging;