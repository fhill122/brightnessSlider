#ifndef TRAYCONFIG_H
#define TRAYCONFIG_H



namespace TrayConfig {

// scale the text
float scale = 1;

//regular background
int background_r = 0;
int background_g = 0;
int background_b = 0;
int background_a = 0;

//charging background
int chargingBackground = 1;
const int C_BACKGROUND_NONE = 0;
const int C_BACKGROUND_IMAGE =1;
// TODO
const int C_BACKGROUND_COLOR =2;
const char chargingBackgroundImage[] = ":/tray/images/charging.png";
int chargingBackground_a = 60;

// text color
int text_r = 255;
int text_g = 255;
int text_b = 255;
int text_a = 255;

//change color if lower than this
int warnPercentage = 30;
int textW_r = 255;
int textW_g = 50;
int textW_b = 0;
int textW_a = 255;

//font
//Note: not every font will align exactly center
char fontFamily[] = "Microsoft Sans Serif";
int fontSize = 32;

//full indicate image
const char chargingFullImage[] = ":/tray/images/chargingFull.png";
const char batteryFullImage[] = ":/tray/images/batteryFull.png";
}

#endif // TRAYCONFIG_H
