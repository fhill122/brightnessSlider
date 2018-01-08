#include "brightnessControl.h"
#include <algorithm>
#include <Windows.h>
#include <ntddvdeo.h>
#include <qdebug.h>
#include <comdef.h>
#include <Wbemidl.h>
#include <powersetting.h>
#include <PowrProf.h>
#include "powermonitor.h"
#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "powrprof.lib")


BrightnessControl::BrightnessControl(){
}


bool BrightnessControl::setBrightness(int level) {

    if (level<0){
        level = 0;
    }
    else if (level >100){
        level = 100;
    }


    HANDLE hDevice = CreateFile(L"\\\\.\\LCD",
                                GENERIC_READ | GENERIC_WRITE,
                                0,NULL,
                                OPEN_EXISTING,
                                0, NULL);
    if (hDevice == INVALID_HANDLE_VALUE) {
        qDebug() << "Brightness set: Invalid handle";
        qDebug() << "Brightness Set:" << GetLastError() << "\n";
        return false;
    }

    DWORD bytesReturned;
    DISPLAY_BRIGHTNESS displayBrightness = DISPLAY_BRIGHTNESS{ DISPLAYPOLICY_BOTH , (UCHAR)level, (UCHAR)level};
    bool result = DeviceIoControl(hDevice, IOCTL_VIDEO_SET_DISPLAY_BRIGHTNESS, &displayBrightness, sizeof(displayBrightness), NULL, 0, &bytesReturned, NULL);
    if (result) {
        current = level;
    }
    else{
        qDebug() << "Brightness Set:" << GetLastError() << "\n";
        return false;
    }

    //update power scheme. (windows sometimes will auto update, sometimes won't, bug?)
    GUID *pActivePolicyGuid;
    DWORD success = PowerGetActiveScheme(NULL, &pActivePolicyGuid);
    if (success!=ERROR_SUCCESS) qDebug() << "SetBrightness: error get active scheme";
    if(PowerMonitor::isOnAC()){
        success = PowerWriteACValueIndex(NULL,pActivePolicyGuid,&GUID_VIDEO_SUBGROUP,&guidDisplayBrightness, level);
    }
    else{
        success = PowerWriteDCValueIndex(NULL,pActivePolicyGuid,&GUID_VIDEO_SUBGROUP,&guidDisplayBrightness, level);
    }
    if (success!=ERROR_SUCCESS) qDebug() << "SetBrightness: error set brightness in power scheme";
    LocalFree(pActivePolicyGuid);

    qDebug()<<"Brightness set to "<<level;
    CloseHandle(hDevice);
    return result;
}

/*
 * Return -1 if failed to get current brightness
 */
int BrightnessControl::getCurrentBrightness(bool refresh){
    if(!refresh)
        return current;

    //get active scheme
    GUID *pActivePolicyGuid;
    DWORD result = PowerGetActiveScheme(NULL, &pActivePolicyGuid);
    if (result!=ERROR_SUCCESS) {
        qDebug() << "getBrightness: error get active scheme";
        return -1;
    }

    //read brightness in power scheme
    DWORD currentBrightness;
    if (PowerMonitor::isOnAC()){
        result = PowerReadACValueIndex(NULL,pActivePolicyGuid,&GUID_VIDEO_SUBGROUP,&guidDisplayBrightness,&currentBrightness);
    }
    else{
        result = PowerReadDCValueIndex(NULL,pActivePolicyGuid,&GUID_VIDEO_SUBGROUP,&guidDisplayBrightness,&currentBrightness);
    }

    if(result!=ERROR_SUCCESS) {
        qDebug()<<"Error get brightness";
        return -1;
    }
    LocalFree(pActivePolicyGuid);
    return currentBrightness;
}

BrightnessControl::~BrightnessControl(){

}
