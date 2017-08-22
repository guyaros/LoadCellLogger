//Sketch name: LoadCellLoggerSketchVer7.0
//Sketch description: Getting data from Load cell using HX711 amplifier and a precision 24-bit analog-to-digital convertor
//Arduino Board: Arduino UNO / Arduino MICRO
//Electronics: SparkFun HX711 Load cell amplifier, Load cell
//Date revised: 27.03.2017
//Created by: Guy Yaros

/*
---== Wiring ==--
Standart load cell use a 4 wires connection:
Excitation+  or VCC      (Commonly colored Red)
Excitation-  or GND     (Commonly colored Black)
Signal+      or Amplifier+    (Commonly colored White)
Signal-      or Ampliifer-    (Commonly colored Green)

Sometimes there is a 5 wire connections, so the fifth wire is a Shield to cencel outside electromagnetic interference  (Commonly colored Yellow)

Please keep in mind that some load cells might have slight variations in color coding.
For example:
Excitation+   colored Red
Excitation-   colored White
Signal+   colored Green
Signal-   colored Black 

--== Amplifier ==--
The load cell is connected to Load Cell Amplifier, using HX711 (integerated circuit/Chip) 24-Bit Analog-to-Digital Converter
Which can be purchased from SparkFun, link bellow:
https://www.sparkfun.com/products/13879
Sparkfun Load Cell Amplifier Pinout:
Red = Excitation+
Black = Excitation-
White = Signal+
Green = Signal-
Yellow = Shield (Optional)
*/

//Sample serial command: @,1,2,15,#
//                       frameHeader,deviceNumber,FunctionNumber,FunctionData1,frameFooter
//@,1,1,1,# Switch on load cell amp
//@,1,1,0,# Switch off load cell amp
//@,1,2,15,# Stream data from load cell (Print to serial load value at full speed)
//@,1,4,-80000,# Set calibration factor
//@,1,5,0,# Print single load cell data (Without frame, only data)


//--== Libraries ==--
#include "HX711.h"

//--== Consts ==--
//Arduino UNO
//#define DATA_PIN  3
//#define CLOCK_PIN  2
//Arduino MICRO
#define DATA_PIN  2
#define CLOCK_PIN  3
#define BOARDLED_PIN 13
#define DEFAULT_CALIBRATION_FACTOR -92391.0

//--== Objects ==--
HX711 scale(DATA_PIN, CLOCK_PIN);

//--== Variables ==--
String tempRxString; //variable to use with serial input
int inputStringLength;
int i;
int j;
int k;
char ch[20];
long inputData[4];
int deviceAddress;
int functionIndex=0;
float functionData;

int tare;
float calibration_factor = DEFAULT_CALIBRATION_FACTOR;
float currentLoadValue;
char outputFrame[50];
char str[30];



void setup()
{
  Serial.begin(115200);
  Serial.setTimeout(10);
  pinMode(BOARDLED_PIN, OUTPUT);
  digitalWrite(BOARDLED_PIN, LOW);
}//End of setup()

void loop()
{
  /*==Serial read & analyze==*/
  if(Serial.available()!= 0) 
  {
 
    /* Serial read */
    tempRxString = Serial.readStringUntil('#'); //Read and store the input string until NULL character

    //Check for frameHeader
    if(tempRxString[0] == '@')
    {
       //If frameHeader exhist, Analyze serial input 
       /* Serial analyze */
      inputStringLength=tempRxString.length(); //Get srting length.
      //Run all over the tempRxString and break it apart.
      for(i=2, j=0, k=0 ; i<=inputStringLength ; i++, j++)
      {
        if(tempRxString[i] != ',')
         {
           ch[j]=tempRxString[i]; //Create a char-array from each "number".
         }
         else if(tempRxString[i] == ',')
         {
           ch[j]='\0';            //Close the char arry so it becomes a String.
           j=-1;                  //Reset the ch array to 0.     
           inputData[k]=atol(ch); //Convert char-array to integer (long). 
           k++;                   //Move forward inputData array.
         }  
      }
          
      deviceAddress=inputData[0];
      functionIndex=inputData[1];
      functionData=inputData[2];
    }
    else
    {
     //If frameStartFlag doesn't exhist -- Do not analyze input
 
    }
    
        
  }//End of serial available

  switch(functionIndex)
  {
    case(0): //functionIndex=0 --> Do not change nothing
    
    break;

    case(1): //functionIndex=1 --> Power toggle load cell
    if(functionData==1)
    {
     scale.power_up(); //Put the HX711 in active mode (15.8mA)
     digitalWrite(BOARDLED_PIN, HIGH); 
     functionIndex=0;
    }
    else if(functionData==0)
    {
      scale.power_down(); //Put the HX711 in sleep mode (70nA)
      digitalWrite(BOARDLED_PIN, LOW);
      functionIndex=0; 
    }  
    break;

    case(2):
    //functionIndex==2 --> Stream load cell live data
    while(Serial.available() <= 0)
    {   
     //Set load cell calibration factor
     scale.set_scale(calibration_factor);
     //Get load cell measurements
     currentLoadValue = scale.get_units();
     //dtostrf(floatvar, StringLengthIncDecimalPoint, numVarsAfterDecimal, charbuf);
     dtostrf(currentLoadValue, 8, 2, str);
     sprintf(outputFrame,"@,%s,#",str);
     Serial.println(outputFrame);
     //Serial.print("@,");
     //Serial.print(currentLoadValue);
     //Serial.println(",#");
    }

    break;

    case(3): //functionIndex==3 --> Tare load cell value
    scale.tare();
    break;

    case(4):  //functionIndex==4 --> Change calibration factor
    calibration_factor=functionData;
    scale.set_scale(calibration_factor);
    functionIndex=0;  
    break;

    case(5):  //functionIndex==5 --> ECHO mode
    delay(100);  
    //Get load cell measurements
     currentLoadValue = scale.get_units();
     //Prit load value (double) to serial
     Serial.println(currentLoadValue);
     //Return to main
     functionIndex=0;
    break;
  
  }//End of switch
  
 
 

}//End of loop()
