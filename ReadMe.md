# Brightness Slider

Author: Ivan B
Email: fhill122@gmail.com
Revision: version#
License:

[TOC]

## Introduction
functions: brightness slider, battery percentage indicator in tray icon


## Power Moniytor Method
** GetSystemPowerStatus function **
https://msdn.microsoft.com/en-us/library/windows/desktop/aa372693(v=vs.85).aspx

** Register power setting notification **
https://msdn.microsoft.com/en-us/library/aa373196(VS.85).aspx

** SystemEvents::PowerModeChanged Event **
https://msdn.microsoft.com/en-us/library/microsoft.win32.systemevents.powermodechanged(v=vs.110).aspx?cs-save-lang=1&cs-lang=cpp#code-snippet-1

issue: Only ac status canbe detected not battery percentage change.
```cs
using Microsoft.Win32;
using System.Diagnostics;
static void Main(string[] args){
	SystemEvents.PowerModeChanged += OnPowerModeChanged;
	System.Threading.Thread.Sleep(1200000000);
}
private static void OnPowerModeChanged(Object sender, PowerModeChangedEventArgs e){
	Debug.WriteLine(e.Mode);
}
```

## Brightness Change Method
** Power Scheme**
Powercfg, or  PowerSetActiveScheme()

** wmisetbrightness **
powershell script
```
$myMonitor = Get-WmiObject -Namespace root\wmi -Class WmiMonitorBrightnessMethods
$myMonitor.wmisetbrightness(0, 50)
```

**Device Control**
Fastest method
https://msdn.microsoft.com/en-us/library/windows/desktop/aa372704(v=vs.85).aspx
https://msdn.microsoft.com/en-us/library/windows/desktop/aa372656(v=vs.85).aspx

```cpp
#include <Windows.h>
#include <Ntddvdeo.h>
void setBrightness(int level) {
	DISPLAY_BRIGHTNESS displayBrightness = DISPLAY_BRIGHTNESS{ DISPLAYPOLICY_BOTH , (UCHAR)level, (UCHAR)level};

	HANDLE hDevice = CreateFile(L"\\\\.\\LCD",
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0, NULL);

	if (hDevice == INVALID_HANDLE_VALUE) {
		cout << "Invalid handle";
		return;
	}

	DWORD bytesReturned;

	bool result = DeviceIoControl(hDevice, IOCTL_VIDEO_SET_DISPLAY_BRIGHTNESS, &displayBrightness, sizeof(displayBrightness), NULL, 0, &bytesReturned, NULL);
	if (!result) {
		cout << GetLastError() << "\n";
	}
}
```

docs:
[Supporting Brightness Controls on Integrated Display Panels](https://docs.microsoft.com/en-us/windows-hardware/drivers/display/supporting-brightness-controls-on-integrated-display-panels)

## Windows message in QT
use nativeEvent

## Monitor Info
### EnumDisplayMonitors
```cpp
BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{

	int *Count = (int*)dwData;
	(*Count)++;

	MONITORINFOEX monitorInfoEx;
	monitorInfoEx.cbSize = sizeof(MONITORINFOEX);
	GetMonitorInfo(hMonitor, &monitorInfoEx);

	cout << monitorInfoEx.szDevice << "\n";

	hDevice = (HANDLE)hMonitor;
	return TRUE;
}

int MonitorCount()
{
	int Count = 0;
	if (EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, (LPARAM)&Count))
		return Count;
	return -1;//signals an error
}
```
### EnumDisplayDevices
Get device handle for using in createFile()
http://stackoverflow.com/questions/42350636/what-is-the-correct-path-when-opening-a-display-with-createfile


## Multi display test

When using DeviceIoControl with handle generated by CreateFile(L"\\\\.\\LCD", ... ), brightness is always set at the internal display.
tested on thinkpad x1 connected to dell 27'' monitor

## Setting transfer
[g*lvj$q$&s]


[g*lvj$q$&s]