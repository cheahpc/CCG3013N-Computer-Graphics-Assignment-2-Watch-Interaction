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
    POWERING_OFF
};
struct System
{
    bool is24HrFormat = false;
    SystemState state = SystemState::OFF;
    AnimState pwrOnAnimState = AnimState::IDLE;

    std::chrono::high_resolution_clock::time_point pOnStartTime, pOffStartTime;
} System;

struct Debug_Object
{
    Object grid = Object(0, 0, 1, 0, COLOR_BLACK, 0);
    Object test = Object(0, 0, 1, 0, COLOR_RED, 10);
    Object ctrlTest1 = Object(100, 100, 1, -45, COLOR_BLUE, 100, 100, 120);
    Object ctrlTest2 = Object(100, 100, 1, -45, COLOR_GREEN, 100);
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
    Object button = Object(WATCH_BUTTON_CENTER_X, WATCH_BUTTON_CENTER_Y, 1, 0, COLOR_GOLD, 100);
    struct Button
    {
        bool isDown = false;
        chrono::high_resolution_clock::time_point downStartTime;
    } Button;
} ObjWatch;

struct UI_Object
{
    Object bg = Object(0, 0, 1, 0, COLOR_THEME_GREEN_DARK_1, 100);
    Object legend = Object(0, 0, 1, 0, COLOR_BLACK, 100);
    Object complication1 = Object(COMPLICATION_X_POS, 0, 0, 0, COLOR_THEME_GREEN_LIGHT_1, 0);
    Object complication2 = Object(COMPLICATION_X_POS, 0, 0, 0, COLOR_THEME_GREEN_LIGHT_1, 0);
    Object complication3 = Object(COMPLICATION_X_POS, 0, 0, 0, COLOR_THEME_GREEN_LIGHT_1, 0);
    Object complication4 = Object(COMPLICATION_X_POS, 0, 0, 0, COLOR_THEME_GREEN_LIGHT_1, 0);

    Object comp4Text = Object(COMP4_TEXT_X_POS, COMP4_TEXT_Y_POS, 0.2, 0, COLOR_WHITE, 0);

    Object time = Object(-90, 70, 0.5, 0, COLOR_WHITE, 0);
    Object dateBox = Object(43, 20, 0.5, 0, COLOR_THEME_GREEN_LIGHT_1, 0);
    Object date = Object(-70, 10, 0.2, 0, COLOR_THEME_GREEN_DARK_3, 0);

    chrono::high_resolution_clock::time_point animStartTime;

    AnimState animState = AnimState::IDLE;

} ObjUI;

struct Legend_Object
{
    Object bg = Object(-650, 0, 1, 0, COLOR_THEME_GREEN_DARK_2, 0);
    Object hintText = Object(-700, 160, 0.10, 0, COLOR_THEME_GREEN_DARK_1, 100);
    Object text = Object();
} ObjLegend;

struct Powering_On_Object
{
    Object bg = Object(0, 0, 1, 0, COLOR_BLACK_1, 0);
    Object logo = Object(-170, -100, 0.55, 0, COLOR_THEME_GREEN, 0);
    Object indicator = Object((-UI_SCREEN_WIDTH / 2) + 40, (UI_SCREEN_HEIGHT / 2) - 40, 1, 0, COLOR_THEME_GREEN_LIGHT_1, 0);
    Object loadingText = Object(-130, -50, 0.20, 0, COLOR_WHITE, 100);
    Object loadingRing = Object(0, 0, 1, 0, COLOR_THEME_GREEN, 100);
    Object loadingRing_Null = Object(0, 0);

    AnimState state = AnimState::IDLE;
} ObjPowerOn;

struct Powering_Off_Object
{
    Object overlay = Object(0, 0, 1, 0, COLOR_BLACK, 0);
    Object bg = Object(0, 70, 1, 0, COLOR_ORANGE, 0);
    Object tittle = Object();
    Object message = Object();
    Object yesText = Object();
    Object noText = Object();
    Object separatorLineHorizontal = Object();
    Object separatorLineVertical = Object();

    AnimState state = AnimState::IDLE;

} ObjPowerOff;