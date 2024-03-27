#include "object.cpp"
#include "color.h"
#include "dimen.h"
#include "renderDebug.cpp"
void kbControl_Debug_Control(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'v':
        debugObj2.translateFlag = !debugObj2.translateFlag;
        break;
    case 'r':
        debugObj1.rotateFlag = !debugObj1.rotateFlag;
        break;
    case 's':
        debugObj1.scaleFlag = !debugObj1.scaleFlag;
        break;
    case 't':
        debugObj1.opacityFlag = !debugObj1.opacityFlag;
        break;
    case 'o':
        debugObj1.orbitFlag = !debugObj1.orbitFlag;
        break;
    case 'c':
        debugObj1.clockWiseFlag = !debugObj1.clockWiseFlag;
        break;
    case 'a': // All
        debugObj2.translateFlag = !debugObj2.translateFlag;
        debugObj1.rotateFlag = !debugObj1.rotateFlag;
        debugObj1.scaleFlag = !debugObj1.scaleFlag;
        debugObj1.opacityFlag = !debugObj1.opacityFlag;
        debugObj1.orbitFlag = !debugObj1.orbitFlag;
        break;

    case 27: // Escape key
        exit(0);
        break;
    }
}


