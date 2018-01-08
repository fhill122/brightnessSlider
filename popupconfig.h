#ifndef POPUPCONFIG_H
#define POPUPCONFIG_H

namespace PopupConfig {

// window pixel size in 1.0 scale ratio
const int WINDOW_W = 360;
const int WINDOW_H = 60;

// popup animation
const int animationDuration = 150;

//background
int background_r = 0;
int background_g = 0;
int background_b = 0;
float background_a = 0.8f;

//time label
const float timeLabel_a = 0.8f;

//brightness icon
const char brightnessIcon[] = ":/popupWindow/images/BrightnessIconWhite.png";

//slider
const int grooveHeight = 10;
bool sysColor = true;
int slider_r = 164;
int slider_g = 192;
int slider_b = 2;

}

#endif // POPUPCONFIG_H
