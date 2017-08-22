#include <rs232.h>
#include <ansi_c.h>
#include <utility.h>
#include <cvirte.h>		
#include <userint.h>
#include "LoadCellLoggerV2.h"


//Functions Prototypes 
int arduinoConnect(void);
int arduinoDisconnect(void);
void CVICALLBACK serialInputFunc (int portNumber, int eventMask, void *callbackData); 
char* createOutputFrame(unsigned int deviceAddress, unsigned int functionIndex, double functionData); 
void sendStringToArduino(unsigned int portNumber, char* tx);
void displayLoadCellData(double loadCellData);
void tareFunc(int mode);
void recordDataToFile(void);
void changeYAxisRange(void);
void gaugeConfigurator(void);
void changeCalibrationFactor(void);
void requestData(void);
void loadUserDefaultSettings(void);


//Panel Handles 
int panelHandle[4];  //Crate a panelHandle array
//panelHandle[1]; //Main panel
//panelHandle[2]; //About panel
//panelHandle[3]; //Settings panel


//Tab handles
int tabHandle[5];
int tabIndex[5];


//Global variables  
int currentTimeHours;
int currentTimeMinutes;
int currentTimeSeconds;
char TimeBufferString[50];
int month;
int day;
int year;
char DateBufferString[20];

int arduinoConnectionStatus=0;
unsigned int portNumber;
int ConnectionTimeout=0.5;
char *tx; 

int startStopToggleButtonState; 

double loadCellOutput=0.0;
double tareValue=0.0;  
int tareDefaultFlag=0;
double loadToDisplay[2];

unsigned int capturedImagesCounter=0;

//Data record
FILE *fp;
int recordDataToFileStatus=0;



int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle[1] = LoadPanel (0, "LoadCellLoggerV2.uir", PANEL01)) < 0)
		return -1;
	if ((panelHandle[2] = LoadPanel (0, "LoadCellLoggerV2.uir", PANEL02)) < 0)
		return -1;
	if ((panelHandle[3] = LoadPanel (0, "LoadCellLoggerV2.uir", PANEL03)) < 0)
		return -1;
	DisplayPanel(panelHandle[1]);
	
	//Get Tab handles from panel
	for(int i=0; i<5 ; i++)
	{
		tabIndex[i] = i;
		GetPanelHandleFromTabPage (panelHandle[3], PANEL03_TAB, tabIndex[i], &tabHandle[i]); 	
	}
	
	//Load user preconfigured settings
	loadUserDefaultSettings();
	//Run user interface
	RunUserInterface();
	
	DiscardPanel(panelHandle[1]);
	return 0;
}

int CVICALLBACK Panel01Func (int panel, int event, void *callbackData,
							 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			if(arduinoConnectionStatus==1)
			{
				arduinoDisconnect();
			}
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK Panel02Func (int panel, int event, void *callbackData,
							 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			HidePanel(panelHandle[2]);
			break;
	}
	return 0;
}

int CVICALLBACK Panel03Func (int panel, int event, void *callbackData,
							 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			HidePanel(panelHandle[3]);
			break;
	}
	return 0;
}



void CVICALLBACK menubarQuit (int menuBar, int menuItem, void *callbackData,
							  int panel)
{
	if(arduinoConnectionStatus==1)
		{
			arduinoDisconnect();
		}
	QuitUserInterface (0);
}

void CVICALLBACK menubarSettings (int menuBar, int menuItem, void *callbackData,
								  int panel)
{
	DisplayPanel(panelHandle[3]);	
}

void CVICALLBACK menubarAbout (int menuBar, int menuItem, void *callbackData,
							   int panel)
{
	DisplayPanel(panelHandle[2]);	
}




void CVICALLBACK menubar1SavePanelChanges (int menuBar, int menuItem, void *callbackData,
		int panel)
{
	SavePanelState (tabHandle[0], "PanelSettings.txt", 0);
	SavePanelState (tabHandle[1], "PanelSettings.txt", 1);
	SavePanelState (tabHandle[2], "PanelSettings.txt", 2);
	SavePanelState (tabHandle[3], "PanelSettings.txt", 3);
}

void CVICALLBACK menubar1LoadSettings (int menuBar, int menuItem, void *callbackData,
									   int panel)
{
	loadUserDefaultSettings();	 
}

void loadUserDefaultSettings()
{
	RecallPanelState (tabHandle[0], "PanelSettings.txt", 0);
	RecallPanelState (tabHandle[1], "PanelSettings.txt", 1);
	RecallPanelState (tabHandle[2], "PanelSettings.txt", 2);
	RecallPanelState (tabHandle[3], "PanelSettings.txt", 3);	
}






int CVICALLBACK CurrentTimeTimerFunc (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
			GetSystemTime (&currentTimeHours, &currentTimeMinutes, &currentTimeSeconds);
			sprintf(TimeBufferString,"%02i:%02i:%02i",currentTimeHours,currentTimeMinutes,currentTimeSeconds);
			SetCtrlVal(panelHandle[1], PANEL01_STRING_CURRENTTIME, TimeBufferString);
			
			GetSystemDate(&month,&day,&year);
			sprintf(DateBufferString,"%02i.%02i.%02i",day,month,year);
			SetCtrlVal(panelHandle[1], PANEL01_STRING_DATE, DateBufferString);
			break;
	}
	return 0;
}



int CVICALLBACK connectionToggleButtonFunc (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	
	
	switch (event)
	{
		case EVENT_COMMIT:
			int buttonState;
			
			GetCtrlVal(panelHandle[1], PANEL01_CONNECTIONTOGGLE, &buttonState);
			if(buttonState == 1)
			{
				arduinoConnectionStatus = arduinoConnect();
				if(arduinoConnectionStatus == 1)
				{
					//Dimm relevant controls
					SetCtrlAttribute (tabHandle[0], TAB0_PORTNUMBER, ATTR_CTRL_MODE, VAL_INDICATOR);
					SetCtrlAttribute (tabHandle[0], TAB0_PORTNUMBER, ATTR_DIMMED, 1);
					SetCtrlAttribute (tabHandle[0], TAB0_BAUDRATERING, ATTR_CTRL_MODE, VAL_INDICATOR);
					SetCtrlAttribute (tabHandle[0], TAB0_BAUDRATERING, ATTR_DIMMED, 1); 
					//unDimm relevant controls
					SetCtrlAttribute (panelHandle[1], PANEL01_STARTSTOPTOGGLE, ATTR_DIMMED, 0);
				}
			}
			else
			{
				arduinoConnectionStatus = arduinoDisconnect();
			}
			break;
	}
	return 0;
}




int arduinoConnect()
{
	char portString[10];
	int baudRate;
	int openPortConfigStatus = -1;
	int connectionStatus=0;
	
	
	//Get Arduino port number from panel
	GetCtrlVal(tabHandle[0], TAB0_PORTNUMBER, &portNumber);
	//Create COM string
	sprintf(portString, "COM%d", portNumber);
	//Get connection Baud rate from panel
	GetCtrlVal(tabHandle[0], TAB0_BAUDRATERING, &baudRate);
	//Configure COM port
	for(int i=0 ; i<5 ; i++)
	{
		openPortConfigStatus = OpenComConfig(portNumber, portString, baudRate, 0, 8, 1, 512, -1);	
	}

	
	if(openPortConfigStatus == 0) //Case COM port successfully opened 
	{
		//Update status varaible
		connectionStatus = 1;
		//Notify user
		//Turn on connection status LED in main panel
		SetCtrlVal(panelHandle[1], PANEL01_CONNECTIONSTATUSLED,1);

		//Listen to serial input from COM port
		SetComTime(portNumber, ConnectionTimeout); //Set communciation timeout (default is 5[sec])
		InstallComCallback (portNumber, LWRS_RXFLAG, 0, '\n', serialInputFunc, 0); //Define an input string to tirgger a callback function
				
	}
	
	else if(openPortConfigStatus < 0)  //Case COM port failed to open
	{
		//Update status varaible 
		connectionStatus = 0;
		//Connect button
		SetCtrlVal(panelHandle[1], PANEL01_CONNECTIONTOGGLE, 0); 
		//Notify user 
		MessagePopup("Connection Error", "Connection failed, Arduino did not found.\nTry to change Port number. \nVerify that the Arduino is connected to PC.");
	}
	
	return connectionStatus;
}



int arduinoDisconnect()
{
	int connectionStatus;
	

	//Request Arduion to Turn off Load Cell amplifier
	 tx=createOutputFrame(1,1,0);
	 sendStringToArduino(portNumber,tx);
	
	//Close com port
	CloseCom(portNumber);
	//Update arduino connection status flag
	connectionStatus = 0;
	//Turn off connection status LED in main panel
	SetCtrlVal(panelHandle[1], PANEL01_CONNECTIONSTATUSLED,0);

	//Dimm relevant controls
	SetCtrlAttribute (panelHandle[1], PANEL01_STARTSTOPTOGGLE, ATTR_DIMMED, 1);
	SetCtrlAttribute (panelHandle[1], PANEL01_TAREBUTTON, ATTR_DIMMED, 1);
	SetCtrlAttribute (panelHandle[1], PANEL01_ABSOLUTEBUTTON, ATTR_DIMMED, 1);
	SetCtrlAttribute (panelHandle[1], PANEL01_CAPTUREBUTTON, ATTR_DIMMED, 1);
	SetCtrlAttribute (panelHandle[1], PANEL01_DATALOGTOGGLEBUTTON , ATTR_DIMMED, 1);
	SetCtrlAttribute (panelHandle[1], PANEL01_CLEARPLOTBUTTON , ATTR_DIMMED, 1);  
	//unDimm relevant controls
	SetCtrlAttribute (tabHandle[0], TAB0_PORTNUMBER, ATTR_CTRL_MODE, VAL_HOT);
	SetCtrlAttribute (tabHandle[0], TAB0_PORTNUMBER, ATTR_DIMMED, 0);
	SetCtrlAttribute (tabHandle[0], TAB0_BAUDRATERING, ATTR_CTRL_MODE, VAL_HOT);
	SetCtrlAttribute (tabHandle[0], TAB0_BAUDRATERING, ATTR_DIMMED, 0);
	//Notify user
	MessagePopup("Connection terminated", "Arduino successfully disconnected.");
	
	return connectionStatus;
}



int CVICALLBACK StartStopToggleFunc (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	

	switch (event)
	{
		case EVENT_COMMIT:
			
			
			GetCtrlVal(panelHandle[1], PANEL01_STARTSTOPTOGGLE, &startStopToggleButtonState);
			if(startStopToggleButtonState==1)
			{
				//Disable stripchart pause (if for some reason it was in pause mode)
				SetCtrlAttribute(panelHandle[1], PANEL01_LOADSTRIPCHART, ATTR_STRIP_CHART_PAUSED, 0);
				
				//Call to tareFunc (mode 3) to handle tare conditions (in this case - get default tare value)
				tareFunc(3);
				
				//Request Arduino to switch on load cell amplifier
				tx=createOutputFrame(1,1,1);
				sendStringToArduino(portNumber,tx);
				
				//Calibration factor
				changeCalibrationFactor();
				
				//Request Arduino to transmit load cell data
				requestData();
				
				
				//unDimm relevant controls
				SetCtrlAttribute (panelHandle[1], PANEL01_CLEARPLOTBUTTON, ATTR_DIMMED, 0);
				SetCtrlAttribute (panelHandle[1], PANEL01_TAREBUTTON, ATTR_DIMMED, 0);
				SetCtrlAttribute (panelHandle[1], PANEL01_ABSOLUTEBUTTON, ATTR_DIMMED, 0);
				SetCtrlAttribute (panelHandle[1], PANEL01_CAPTUREBUTTON, ATTR_DIMMED, 0);
				SetCtrlAttribute (panelHandle[1], PANEL01_DATALOGTOGGLEBUTTON , ATTR_DIMMED, 0);
				
			}
			else
			{
				//Request Arduino to switch off load cell amplifier 
				tx=createOutputFrame(1,1,0);
				sendStringToArduino(portNumber,tx);
				//Pause stripchart so the plot can be scrolled sideways
				SetCtrlAttribute(panelHandle[1], PANEL01_LOADSTRIPCHART, ATTR_STRIP_CHART_PAUSED, 1);
			}
			
			break;
	}
	return 0;
}



void requestData()
{
	
	//Check start/stop button state
	GetCtrlVal(panelHandle[1], PANEL01_STARTSTOPTOGGLE, &startStopToggleButtonState); 
	if(startStopToggleButtonState==1)
	{
		//Flush serial input buffer
		FlushInQ (portNumber);
		//FlushOutQ(portNumber);
		//Request Arduino to transmit single load cell data
		tx=createOutputFrame(1,5,0);
		//Send string to arduino 
		sendStringToArduino(portNumber,tx);	
	}
	
		
}



void CVICALLBACK serialInputFunc (int portNumber, int eventMask, void *callbackData)
{
 #define SIZE_OF_SERIAL_INPUT 20
 #define MAX_INPUT_CHARS 20	
 #define MAX_INPUT_DATA_ELEMENTS 1 

 char serialInput[SIZE_OF_SERIAL_INPUT];
 int numberOfbytesRead;

 int inputQueueLength; 

	

 	//Check start/stop button state
 	GetCtrlVal(panelHandle[1], PANEL01_STARTSTOPTOGGLE, &startStopToggleButtonState);
	
	if(startStopToggleButtonState==1)
	{
		inputQueueLength=1;
		while(inputQueueLength > 0)
		{
			//Read serial input from Arduino and store it into a temporary string
	 		numberOfbytesRead = ComRdTerm(portNumber, serialInput, MAX_INPUT_CHARS, '\n');
			
			//Convert the input to string by adding \0
		serialInput[numberOfbytesRead-1]='\0';
		
		SetCtrlVal(panelHandle[1], PANEL01_INPUTSTRING, serialInput); //DEBUG ONLY 
		//Convert serial string to double
		loadCellOutput = atof(serialInput);
		
		//Multiply by -1 to get inverse load value (For a specific usage) 
		loadCellOutput = (loadCellOutput*-1);
		
		//Call to function that handles display
		 displayLoadCellData(loadCellOutput);
			
		//Peek the serial input buffer, and count the numbers of chars in the serial input buffer
		inputQueueLength = GetInQLen(portNumber);
		}
		
		//Call to function that request data from Arduino
		requestData();
	
   }//End of if(startStopToggleButtonState==1)  
	
}







char* createOutputFrame(unsigned int deviceAddress, unsigned int functionIndex, double functionData)
{
	#define MAX_FRAME_CHARS 25  
	
	char outputFrame[MAX_FRAME_CHARS];
	char frameHeader='@';
	char frameFooter='#';
	int frameLength;
	
	//Create an output frame  (frameHeader,deviceAddress,functionIndex,functionData,frameFooter) 
	sprintf(outputFrame,"%c,%d,%d,%0.0lf,%c", frameHeader,deviceAddress,functionIndex,functionData,frameFooter);
	
	//Create pointer from char array
	frameLength=strlen(outputFrame);
	char *outputFrameString = (char *) malloc(sizeof(char) * (frameLength+1));
	strcpy(outputFrameString,outputFrame);
	
	return outputFrameString;
}



void sendStringToArduino(unsigned int portNumber, char* tx)
{
	int txStringlength;

	//Count the number of chars in string
	txStringlength = strlen(tx);
	//Write string (bytes) to COM port
	ComWrt(portNumber,tx, txStringlength);	
}





void displayLoadCellData(double loadCellData)
{
	
	loadToDisplay[0] = 0.0;
	loadToDisplay[1] =  loadCellData - tareValue;
	
	//Display current load to digital numeric display
 	SetCtrlVal(panelHandle[1], PANEL01_CURRENTLOADDISP, loadToDisplay[1]);
	
	//Display data to Gauge
	SetCtrlVal(panelHandle[1], PANEL01_LOADGAUGE, loadToDisplay[1]);
	
	//Plot points to strip chart 
	PlotStripChart(panelHandle[1], PANEL01_LOADSTRIPCHART, loadToDisplay, 2, 0, 0, VAL_DOUBLE);
	
	if(recordDataToFileStatus==1)
	{
		//Call to the function that handles the data logging
		recordDataToFile();	
	}
	
	
}





int CVICALLBACK numericCalibrationFactorFunc (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
	{
		case EVENT_COMMIT:
			changeCalibrationFactor();
			break;
	}
	return 0;
}




void changeCalibrationFactor()
{
	double loadCellCalibrationFactor;
 
		//Get calibration factor from Settings tab
		GetCtrlVal(tabHandle[1], TAB1_CALIBRATIONFACTOR, &loadCellCalibrationFactor);
		
		if(arduinoConnectionStatus==1) //If Arduino is connected to load cell
		{
			//Request Arduino to change calibration factor
			tx=createOutputFrame(1,4,loadCellCalibrationFactor);
			//Trasmit string to arduino
			sendStringToArduino(portNumber,tx);
		}		
}



int CVICALLBACK clearPlotButtonFunc (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			ClearStripChart(panelHandle[1], PANEL01_LOADSTRIPCHART);
			//displayLoadCellData(zero);
			break;
	}
	return 0;
}



int CVICALLBACK tareButtonFunc (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			tareFunc(1);
			break;
	}
	return 0;
}


void tareFunc(int mode)
{
	startStopToggleButtonState=0;
	
	if(mode == 0)
	{
		tareValue = 0.0; 	
	}
	else if(mode == 1)
	{
		tareValue = loadCellOutput; 	
	}
	else if(mode == 3)
	{
		if(tareDefaultFlag == 0)
		{
			GetCtrlVal(tabHandle[1], TAB1_DEFAULTTAREVALUE, &tareValue);
			tareDefaultFlag=1;
		}
		
	}
	else if(mode==4)
	{
		GetCtrlVal(tabHandle[1], TAB1_DEFAULTTAREVALUE, &tareValue);	
	}
	
	
	SetCtrlVal(panelHandle[1], PANEL01_TAREVALUE, tareValue);
	startStopToggleButtonState=1; 
}



int CVICALLBACK absoluteButtonFunc (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			tareValue = 0.0;
			SetCtrlVal(panelHandle[1], PANEL01_TAREVALUE, tareValue);
			break;
	}
	return 0;
}



int CVICALLBACK captureButtonFunc (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	
	
	switch (event)
	{
		case EVENT_COMMIT:
			char buttonLabel[20];
			int bitmap_id;
			char userPath[100];
			char fileName[100];
			char extension[10];
			char dateStamp[15];
			char timeStamp[10];
	
			//Change button label
			capturedImagesCounter++;
			sprintf(buttonLabel,"Captured (%d)",capturedImagesCounter);
			SetCtrlAttribute (panelHandle[1], PANEL01_CAPTUREBUTTON, ATTR_LABEL_TEXT, buttonLabel);
			//Capture panel and create bitmap
			GetPanelDisplayBitmap (panelHandle[1], VAL_VISIBLE_AREA, VAL_ENTIRE_OBJECT, &bitmap_id);
			//Get user path for the file output
			GetCtrlVal(tabHandle[3], TAB3_PATHSTRING, userPath);
			//Copy user path to fileName string
			strcpy(fileName,userPath);
			//Create a date string
			sprintf(dateStamp,"%02i.%02i.%02i",day,month,year);
			//Add to fileName string the date stamp 
			strcat(fileName,dateStamp);
			//Create a time string
			sprintf(timeStamp,"%02i-%02i-%02i",currentTimeHours,currentTimeMinutes,currentTimeSeconds); 
			//Add to fileName string the time stamp 
			strcat(fileName,timeStamp);
			//Create a file extension string
			sprintf(extension,".jpg");
			//Add to fileName the file extension
			strcat(fileName,extension);
			//Save capture as image file to desired path
			SaveBitmapToJPEGFile (bitmap_id, fileName, JPEG_DCTFLOAT, 100);
			
			
			break;
	}
	return 0;
}



int CVICALLBACK recordToggleButtonFunc (int panel, int control, int event,
										void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
	{
		case EVENT_COMMIT:
		int recordButtonState;
		char recordFilePath[50];
		char headerString[30];
	
			GetCtrlVal(panelHandle[1], PANEL01_DATALOGTOGGLEBUTTON, &recordButtonState);
			if(recordButtonState==1)
			{
				//Switch on record LED 
				SetCtrlVal(panelHandle[1], PANEL01_RECORDSTATUSLED,1);
				
				//Get file name
				GetCtrlVal(tabHandle[4], TAB4_RECRODFILENAME, recordFilePath);
				//Add file extension
				strcat (recordFilePath, ".csv");
				
				//Create new file (.csv format), in write mode. if file exhist, rewrite it
				fp=fopen(recordFilePath,"w");
				
				//Write header to file
				sprintf(headerString, "Load[kg],Hour,Minute,Second");
				fprintf(fp,headerString); 
		  		fprintf(fp,"\n");
				
				//Update record status
				recordDataToFileStatus=1;
				
			}
			else if(recordButtonState==0)
			{
				//Switch off record LED
				SetCtrlVal(panelHandle[1], PANEL01_RECORDSTATUSLED,0);
				//Update record status  
				recordDataToFileStatus=0; 
			}
			
			break;
	}
	return 0;
}

void recordDataToFile()
{
		char string[150];
		
		  //Create a string in CSV format
		  sprintf(string, "%lf,%02d,%02d,%02d", loadToDisplay[1],currentTimeHours,currentTimeMinutes,currentTimeSeconds);
		  //Write data to file  
		  fprintf(fp,string); 
		  fprintf(fp,"\n");

}

int CVICALLBACK numericYAxisMaxFunc (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
	{
		case EVENT_COMMIT:
			changeYAxisRange();
			break;
	}
	return 0;
}



int CVICALLBACK numericYAxisMinFunc (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			changeYAxisRange();
			break;
	}
	return 0;
}


void changeYAxisRange()
{
	double loadCellMinValue;
	double loadCellMaxValue; 
	
	GetCtrlVal(tabHandle[2], TAB2_PLOTYMIN, &loadCellMinValue);
	GetCtrlVal(tabHandle[2], TAB2_PLOTYMAX, &loadCellMaxValue);
	
	if(loadCellMaxValue > loadCellMinValue)
	{
		SetCtrlAttribute(tabHandle[2], TAB2_TEXTWARNING, ATTR_VISIBLE,0);
		SetAxisRange (panelHandle[1], PANEL01_LOADSTRIPCHART, VAL_NO_CHANGE, 0.0, 1.0, VAL_MANUAL, (loadCellMinValue), (loadCellMaxValue));	
	}
	else
	{
		SetCtrlAttribute(tabHandle[2], TAB2_TEXTWARNING, ATTR_VISIBLE,1);
	}
 	
}




int CVICALLBACK RingGaugeDisplayFunc (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	 
	switch (event)
	{
		case EVENT_COMMIT:
			int gaugeDisplayMode;
			
			GetCtrlVal(tabHandle[2], TAB2_RINGGAUGEDISPLAY, &gaugeDisplayMode);
			SetCtrlAttribute (panelHandle[1], PANEL01_LOADGAUGE, ATTR_VISIBLE, gaugeDisplayMode);
			SetCtrlAttribute (panelHandle[1], PANEL01_CURRENTLOADDISP, ATTR_VISIBLE, gaugeDisplayMode); 
			break;
	}
	return 0;
}

void gaugeConfigurator()
{
	
	//SetNumericColorRamp()
}



int CVICALLBACK loadCellRing (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			unsigned int loadCellRingVal; 
			GetCtrlVal(tabHandle[1], TAB1_LOADCELLRING, &loadCellRingVal);
			if(loadCellRingVal==40)
			{
				SetCtrlVal(tabHandle[1], TAB1_LOADCELLMAXLOAD, 40);
				SetCtrlVal(tabHandle[1], TAB1_CALIBRATIONFACTOR, -90430.00);
				SetCtrlVal(tabHandle[1], TAB1_DEFAULTTAREVALUE, -92.19);
			}
			else if(loadCellRingVal==20)
			{
				SetCtrlVal(tabHandle[1], TAB1_LOADCELLMAXLOAD, 20);
				SetCtrlVal(tabHandle[1], TAB1_CALIBRATIONFACTOR, -191000.00);
				SetCtrlVal(tabHandle[1], TAB1_DEFAULTTAREVALUE, -42.99);	
			}
			else if(loadCellRingVal==10)
			{
				SetCtrlVal(tabHandle[1], TAB1_LOADCELLMAXLOAD, 10);
				SetCtrlVal(tabHandle[1], TAB1_CALIBRATIONFACTOR, -193000.00);
				SetCtrlVal(tabHandle[1], TAB1_DEFAULTTAREVALUE, -50.00);	
			}
				else if(loadCellRingVal==4)
			{
				SetCtrlVal(tabHandle[1], TAB1_LOADCELLMAXLOAD, 4);
				SetCtrlVal(tabHandle[1], TAB1_CALIBRATIONFACTOR, -69000.00);
				SetCtrlVal(tabHandle[1], TAB1_DEFAULTTAREVALUE, -10.00);	
			}
			
			changeCalibrationFactor(); 
			tareFunc(4);
			
			break;
	}
	return 0;
}

int CVICALLBACK setGaugeColorsFunc (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	#define NUMBER_OF_COLORS 8
	ColorMapEntry colorsArray[NUMBER_OF_COLORS];
	double colorMax[NUMBER_OF_COLORS];
	int colorNum[NUMBER_OF_COLORS];
	int i;
	int dataRangeOk=1;
	char dataErrorString[20];
	
	switch (event)
	{
		case EVENT_COMMIT:
			
		//Get color ranges from panel
		GetCtrlVal(tabHandle[2], TAB2_COLORMAX0, &colorMax[0]);
		GetCtrlVal(tabHandle[2], TAB2_COLORMAX1, &colorMax[1]);
		GetCtrlVal(tabHandle[2], TAB2_COLORMAX2, &colorMax[2]);
		GetCtrlVal(tabHandle[2], TAB2_COLORMAX3, &colorMax[3]);
		GetCtrlVal(tabHandle[2], TAB2_COLORMAX4, &colorMax[4]);
		GetCtrlVal(tabHandle[2], TAB2_COLORMAX5, &colorMax[5]);
		GetCtrlVal(tabHandle[2], TAB2_COLORMAX6, &colorMax[6]);
		
		//Validate user input
		for(i=0 ; i<6 ; i++)
		{
			if(colorMax[i] >= colorMax[i+1])
			{
				sprintf(dataErrorString, "Check ranges (%d)",i);
				MessagePopup("Data range error", dataErrorString);
				dataRangeOk=0;
			}

		}
		

		for(i=0 ; i<NUMBER_OF_COLORS-1 ; i++)
		{
			colorsArray[i].dataValue.valDouble = colorMax[i];
		}
			
		//Get color shades from panel 
	    GetCtrlVal(tabHandle[2], TAB2_COLORNUM0, &colorNum[0]); 
		GetCtrlVal(tabHandle[2], TAB2_COLORNUM1, &colorNum[1]); 
		GetCtrlVal(tabHandle[2], TAB2_COLORNUM2, &colorNum[2]); 
		GetCtrlVal(tabHandle[2], TAB2_COLORNUM3, &colorNum[3]); 
		GetCtrlVal(tabHandle[2], TAB2_COLORNUM4, &colorNum[4]); 
		GetCtrlVal(tabHandle[2], TAB2_COLORNUM5, &colorNum[5]); 
		GetCtrlVal(tabHandle[2], TAB2_COLORNUM6, &colorNum[6]); 
		GetCtrlVal(tabHandle[2], TAB2_COLORNUM7, &colorNum[7]); 

		
		for(i=0 ; i<NUMBER_OF_COLORS ; i++)
		{
			colorsArray[i].color = colorNum[i];	
		}
		
		
		
		 //Set gauge colors, if the ranges are ok
		 if(dataRangeOk==1)
		 {
		 	SetNumericColorRamp (panelHandle[1], PANEL01_LOADGAUGE, colorsArray, colorNum[NUMBER_OF_COLORS-1], NUMBER_OF_COLORS, 0);
		 }
		 
		 
			break;
	}
	return 0;
}

int CVICALLBACK colorMax0Func (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	double colorMax0; 
	
	switch (event)
	{
		case EVENT_VAL_CHANGED:
			GetCtrlVal(tabHandle[2], TAB2_COLORMAX0, &colorMax0);
			SetCtrlVal(tabHandle[2], TAB2_COLORMIN1, colorMax0);
			break;
	}
	return 0;
}

int CVICALLBACK colorMax1Func (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	double colorMax1;
	
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(tabHandle[2], TAB2_COLORMAX1, &colorMax1);
			SetCtrlVal(tabHandle[2], TAB2_COLORMIN2, colorMax1);
			break;
	}
	return 0;
}

int CVICALLBACK colorMax2Func (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	double colorMax2;
	
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(tabHandle[2], TAB2_COLORMAX2, &colorMax2);
			SetCtrlVal(tabHandle[2], TAB2_COLORMIN3, colorMax2);
			break;
	}
	return 0;
}

int CVICALLBACK colorMax3Func (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	double colorMax3;
	
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(tabHandle[2], TAB2_COLORMAX3, &colorMax3);
			SetCtrlVal(tabHandle[2], TAB2_COLORMIN4, colorMax3);
			break;
	}
	return 0;
}

int CVICALLBACK colorMax4Func (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	double colorMax4;
	
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(tabHandle[2], TAB2_COLORMAX4, &colorMax4);
			SetCtrlVal(tabHandle[2], TAB2_COLORMIN5, colorMax4);
			break;
	}
	return 0;
}

int CVICALLBACK colorMax5Func (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	double colorMax5;
	
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(tabHandle[2], TAB2_COLORMAX5, &colorMax5);
			SetCtrlVal(tabHandle[2], TAB2_COLORMIN6, colorMax5);
			break;
	}
	return 0;
}

int CVICALLBACK colorMax6Func (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	double colorMax6;
	
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(tabHandle[2], TAB2_COLORMAX6, &colorMax6);
			SetCtrlVal(tabHandle[2], TAB2_COLORMIN7, colorMax6);
			break;
	}
	return 0;
}


int CVICALLBACK gaugeMaxFunc (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	double gaugeMax;

	switch (event)
	{
		case EVENT_VAL_CHANGED:
			GetCtrlVal(tabHandle[2], TAB2_GAUGEMAX, &gaugeMax);
			SetCtrlAttribute (panelHandle[1], PANEL01_LOADGAUGE, ATTR_MAX_VALUE, gaugeMax);
			break;
	}
	return 0;
}

int CVICALLBACK gaugeMinFunc (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
		double gaugeMin;
	switch (event)
	{
		case EVENT_VAL_CHANGED:
			GetCtrlVal(tabHandle[2], TAB2_GAUGEMIN, &gaugeMin);
		 	SetCtrlAttribute (panelHandle[1], PANEL01_LOADGAUGE, ATTR_MIN_VALUE, gaugeMin);
			break;
	}
	return 0;
}


