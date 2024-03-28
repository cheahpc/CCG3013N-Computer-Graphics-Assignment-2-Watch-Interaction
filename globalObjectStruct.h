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
        chrono::high_resolution_clock::time_point downTime;
    } Button;
} ObjWatch;

struct UI_Object
{
    Object bg = Object(0, 0, 1, 0, COLOR_THEME_GREEN_LIGHT_1, 20);
    Object boot = Object(0, 0, 1, 0, COLOR_BLACK, 100);
    Object powerOff = Object(0, 0, 1, 0, COLOR_BLACK, 100);
    Object legend = Object(0, 0, 1, 0, COLOR_BLACK, 100);
    Object complication1 = Object();
    Object complication2 = Object();
    Object complication3 = Object();
    Object complication4 = Object();
    Object time = Object(-90, 70, 0.5, 0, COLOR_WHITE, 0);
    Object date = Object(-70, 20, 0.2, 0, COLOR_WHITE, 0);


    struct DateTime
    {
        bool isShow= false;
        bool isAnimating = false;
    } DateTime;
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
    Object loadingRing1 = Object(0, 0, 1, 0, COLOR_THEME_GREEN, 100);
    Object loadingRing1_null = Object(0, 0);
} ObjPowerOn;
