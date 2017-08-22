/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL01                          1       /* callback function: Panel01Func */
#define  PANEL01_CONNECTIONTOGGLE         2       /* control type: textButton, callback function: connectionToggleButtonFunc */
#define  PANEL01_ABSOLUTEBUTTON           3       /* control type: command, callback function: absoluteButtonFunc */
#define  PANEL01_TAREBUTTON               4       /* control type: command, callback function: tareButtonFunc */
#define  PANEL01_CONNECTIONSTATUSLED      5       /* control type: LED, callback function: (none) */
#define  PANEL01_CURRENTLOADDISP          6       /* control type: numeric, callback function: (none) */
#define  PANEL01_LOADGAUGE                7       /* control type: scale, callback function: (none) */
#define  PANEL01_DATALOGTOGGLEBUTTON      8       /* control type: textButton, callback function: recordToggleButtonFunc */
#define  PANEL01_CAPTUREBUTTON            9       /* control type: command, callback function: captureButtonFunc */
#define  PANEL01_STRING_CURRENTTIME       10      /* control type: string, callback function: (none) */
#define  PANEL01_STRING_DATE              11      /* control type: string, callback function: (none) */
#define  PANEL01_TIMER                    12      /* control type: timer, callback function: CurrentTimeTimerFunc */
#define  PANEL01_STARTSTOPTOGGLE          13      /* control type: textButton, callback function: StartStopToggleFunc */
#define  PANEL01_TAREVALUE                14      /* control type: numeric, callback function: (none) */
#define  PANEL01_INPUTSTRING              15      /* control type: string, callback function: (none) */
#define  PANEL01_DECORATION               16      /* control type: deco, callback function: (none) */
#define  PANEL01_CLEARPLOTBUTTON          17      /* control type: command, callback function: clearPlotButtonFunc */
#define  PANEL01_LOADSTRIPCHART           18      /* control type: strip, callback function: (none) */
#define  PANEL01_RECORDSTATUSLED          19      /* control type: LED, callback function: (none) */

#define  PANEL02                          2       /* callback function: Panel02Func */
#define  PANEL02_GUYAROSLOGO              2       /* control type: picture, callback function: (none) */
#define  PANEL02_TEXT_DATE                3       /* control type: textMsg, callback function: (none) */
#define  PANEL02_TEXT_MADEBY              4       /* control type: textMsg, callback function: (none) */
#define  PANEL02_TEXT_SKETCHNAME          5       /* control type: textMsg, callback function: (none) */
#define  PANEL02_TEXT_VERSION             6       /* control type: textMsg, callback function: (none) */

#define  PANEL03                          3       /* callback function: Panel03Func */
#define  PANEL03_TAB                      2       /* control type: tab, callback function: (none) */

     /* tab page panel controls */
#define  TAB0_BAUDRATERING                2       /* control type: ring, callback function: (none) */
#define  TAB0_PORTNUMBER                  3       /* control type: numeric, callback function: (none) */

     /* tab page panel controls */
#define  TAB1_LOADCELLMAXLOAD             2       /* control type: numeric, callback function: (none) */
#define  TAB1_CALIBRATIONFACTOR           3       /* control type: numeric, callback function: numericCalibrationFactorFunc */
#define  TAB1_SAMPLINGFREQ                4       /* control type: numeric, callback function: (none) */
#define  TAB1_LOADCELLRING                5       /* control type: ring, callback function: loadCellRing */
#define  TAB1_TEXTMSG_2                   6       /* control type: textMsg, callback function: (none) */
#define  TAB1_DEFAULTTAREVALUE            7       /* control type: numeric, callback function: (none) */
#define  TAB1_TEXTMSG                     8       /* control type: textMsg, callback function: (none) */

     /* tab page panel controls */
#define  TAB2_PLOTYMIN                    2       /* control type: numeric, callback function: numericYAxisMinFunc */
#define  TAB2_SETCOLORSBUTTON             3       /* control type: command, callback function: setGaugeColorsFunc */
#define  TAB2_COLORMAX0                   4       /* control type: numeric, callback function: colorMax0Func */
#define  TAB2_COLORMIN7                   5       /* control type: numeric, callback function: (none) */
#define  TAB2_COLORMIN6                   6       /* control type: numeric, callback function: (none) */
#define  TAB2_COLORMIN5                   7       /* control type: numeric, callback function: (none) */
#define  TAB2_COLORMIN4                   8       /* control type: numeric, callback function: (none) */
#define  TAB2_COLORNUM6                   9       /* control type: color, callback function: (none) */
#define  TAB2_COLORMAX6                   10      /* control type: numeric, callback function: colorMax6Func */
#define  TAB2_TEXTMSG_13                  11      /* control type: textMsg, callback function: (none) */
#define  TAB2_COLORMIN3                   12      /* control type: numeric, callback function: (none) */
#define  TAB2_COLORNUM5                   13      /* control type: color, callback function: (none) */
#define  TAB2_COLORMAX5                   14      /* control type: numeric, callback function: colorMax5Func */
#define  TAB2_TEXTMSG_11                  15      /* control type: textMsg, callback function: (none) */
#define  TAB2_COLORNUM7                   16      /* control type: color, callback function: (none) */
#define  TAB2_COLORNUM4                   17      /* control type: color, callback function: (none) */
#define  TAB2_COLORMAX4                   18      /* control type: numeric, callback function: colorMax4Func */
#define  TAB2_TEXTMSG_9                   19      /* control type: textMsg, callback function: (none) */
#define  TAB2_COLORMIN2                   20      /* control type: numeric, callback function: (none) */
#define  TAB2_COLORNUM3                   21      /* control type: color, callback function: (none) */
#define  TAB2_COLORMAX3                   22      /* control type: numeric, callback function: colorMax3Func */
#define  TAB2_TEXTMSG_6                   23      /* control type: textMsg, callback function: (none) */
#define  TAB2_COLORMIN1                   24      /* control type: numeric, callback function: (none) */
#define  TAB2_COLORNUM2                   25      /* control type: color, callback function: (none) */
#define  TAB2_COLORMAX2                   26      /* control type: numeric, callback function: colorMax2Func */
#define  TAB2_TEXTMSG_4                   27      /* control type: textMsg, callback function: (none) */
#define  TAB2_COLORNUM0                   28      /* control type: color, callback function: (none) */
#define  TAB2_COLORNUM1                   29      /* control type: color, callback function: (none) */
#define  TAB2_COLORMAX1                   30      /* control type: numeric, callback function: colorMax1Func */
#define  TAB2_TEXTMSG_14                  31      /* control type: textMsg, callback function: (none) */
#define  TAB2_TEXTMSG_3                   32      /* control type: textMsg, callback function: (none) */
#define  TAB2_TEXTMSG_15                  33      /* control type: textMsg, callback function: (none) */
#define  TAB2_TEXTMSG_5                   34      /* control type: textMsg, callback function: (none) */
#define  TAB2_TEXTMSG_7                   35      /* control type: textMsg, callback function: (none) */
#define  TAB2_TEXTMSG_12                  36      /* control type: textMsg, callback function: (none) */
#define  TAB2_TEXTMSG_16                  37      /* control type: textMsg, callback function: (none) */
#define  TAB2_TEXTMSG_10                  38      /* control type: textMsg, callback function: (none) */
#define  TAB2_TEXTMSG_8                   39      /* control type: textMsg, callback function: (none) */
#define  TAB2_TEXTMSG_17                  40      /* control type: textMsg, callback function: (none) */
#define  TAB2_PLOTYMAX                    41      /* control type: numeric, callback function: numericYAxisMaxFunc */
#define  TAB2_TEXTMSG                     42      /* control type: textMsg, callback function: (none) */
#define  TAB2_RINGGAUGEDISPLAY            43      /* control type: ring, callback function: RingGaugeDisplayFunc */
#define  TAB2_TEXTWARNING                 44      /* control type: textMsg, callback function: (none) */
#define  TAB2_TEXTMSG_2                   45      /* control type: textMsg, callback function: (none) */
#define  TAB2_GAUGEMIN                    46      /* control type: numeric, callback function: gaugeMinFunc */
#define  TAB2_GAUGEMAX                    47      /* control type: numeric, callback function: gaugeMaxFunc */

     /* tab page panel controls */
#define  TAB3_PATHSTRING                  2       /* control type: string, callback function: (none) */
#define  TAB3_TEXTMSG                     3       /* control type: textMsg, callback function: (none) */

     /* tab page panel controls */
#define  TAB4_RECRODFILENAME              2       /* control type: string, callback function: (none) */
#define  TAB4_TEXTMSG                     3       /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_MENU                     2
#define  MENUBAR_MENU_QUIT                3       /* callback function: menubarQuit */
#define  MENUBAR_MENU1                    4       /* callback function: menubarSettings */
#define  MENUBAR_HELP                     5
#define  MENUBAR_HELP_ITEM3               6
#define  MENUBAR_HELP_ABOUT               7       /* callback function: menubarAbout */

#define  MENUBAR1                         2
#define  MENUBAR1_SAVECHANGES             2       /* callback function: menubar1SavePanelChanges */
#define  MENUBAR1_LOADSETTINGS            3       /* callback function: menubar1LoadSettings */


     /* Callback Prototypes: */

int  CVICALLBACK absoluteButtonFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK captureButtonFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK clearPlotButtonFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK colorMax0Func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK colorMax1Func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK colorMax2Func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK colorMax3Func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK colorMax4Func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK colorMax5Func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK colorMax6Func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK connectionToggleButtonFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CurrentTimeTimerFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK gaugeMaxFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK gaugeMinFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK loadCellRing(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK menubar1LoadSettings(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menubar1SavePanelChanges(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menubarAbout(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menubarQuit(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK menubarSettings(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK numericCalibrationFactorFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK numericYAxisMaxFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK numericYAxisMinFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Panel01Func(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Panel02Func(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Panel03Func(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK recordToggleButtonFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RingGaugeDisplayFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK setGaugeColorsFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StartStopToggleFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK tareButtonFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
