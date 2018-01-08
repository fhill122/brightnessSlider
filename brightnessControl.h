#ifndef BRIGHTNESSCONTROL_H
#define BRIGHTNESSCONTROL_H

#include <Wbemidl.h>
#include <windows.h>
#include <vector>

class BrightnessControl{
private:
    int current = -1;
    const GUID guidDisplayBrightness = {0xaded5e82, 0xb909, 0x4619, {0x99, 0x49, 0xf5, 0xd7, 0x1d, 0xac, 0x0b, 0xcb}};


public:


private:
    bool getSupportedBrightness(BYTE* levels, int *n);

public:
    BrightnessControl();
    ~BrightnessControl();
    int getCurrentBrightness(bool refresh = false);
    bool setBrightness(int level);
};

#endif // BRIGHTNESSCONTROL_H
