#ifndef TRAYCONFIG_H
#define TRAYCONFIG_H



namespace TrayConfig {
// scale the text
const float scale = 1;

//background
const int background_r = 0;
const int background_g = 0;
const int background_b = 0;
const int background_a = 0;
const char chargingBackgroundImage[] = ":/tray/images/charging.png";

//font
//Note: not every font will align exactly center
const char fontFamily[] = "Microsoft Sans Serif";
const int fontSize = 32;

//full indicate image
const char chargingFullImage[] = ":/tray/images/chargingFull.png";
const char batteryFullImage[] = ":/tray/images/batteryFull.png";
}

#endif // TRAYCONFIG_H
