#include <Arduino.h> //#include "Arduino.h" For Arduino Framework Logic
#include <string>
#include <cstring>
#include <Wire.h> //#include "Wire.h" For TWI/I2C Hardware Configuration
#include "EnumBoolen.h" //#include "Mm.h" For Enum Logic
#include "Debug.h" //#include "Mm.h" For Enum Logic
#include "RTK.h" //#include "RTK.h"
#include "Ebyte.h"
#define BTpin PB15

// stm pa2, pa3 
Flasher LedBD(PC13, 100, 400);//Led on Board Pin 13
Flasher LedRTK(PB12, 100, 1000);//Led on Board Pin 13
Flasher LedBL(PB13, 100, 1000);//Led on Board Pin 13
HardwareSerial BLSERIAL(PB11, PB10);//#define BLSERIAL Serial1 RX:TX(PB11,PB10)
HardwareSerial RTKSERIAL(PA9, PA10); //#define RTKSERIAL Serial2 RX:TX(PA10,PA9) 
HardwareSerial EBSERIAL(PA2, PA3); //#define EYBTESERIAL Serial2 RX:TX(PA2,12) 
BL_State Bl_Con(PB15);  //class ButtState
EBYTE EBSerial (&EBSERIAL, PB0, PB1);
RTK RTKSerial(RTKSERIAL, LedRTK); //Define TelemSerial to class TELEM with LedTlm


unsigned long PreviousMillis_BL = 0;// will store last time MAVLink was transmitted and listened
unsigned long PreviousMillis_MAVLink_DS = 0;// will store last time MAVLink was transmitted and listened

unsigned long Next_Interval_BL = 100;// next interval to count
unsigned long Next_Interval_MAVLink_DS = 100;// next interval to count

unsigned long PreviousMillis_Timer = 0;// will store last time MAVLink was transmitted and listened
unsigned long PreviousMillis_Timer2 = 0;// will store last time MAVLink was transmitted and listened

unsigned long Next_Interval_Timer = 10;// next interval to count
unsigned long Next_Interval_Timer2 = 100;// next interval to count
//#Variable configuration#//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#######################
String readString;
int Blstate;
int Modes;
byte Address= 0;
int Channel= 0;
long Interval_Connection = 0;
void BL_Sending(){

}
void RTK_Connection_Configuration(){
  RTKSerial.begin_config(115200); // set the data rate for the TelemSerial port
}
void RTK_Connection_Default(){
  RTKSerial.begin_default(38400); // set the data rate for the TelemSerial port
}
void BL_Connection(){
  BLSERIAL.begin(115200); // set the data rate for the TelemSerial port
}
void EB_Connection(){
  EBSERIAL.begin(38400); // set the data rate for the TelemSerial port
}

void Mode_Info(){
  BLSERIAL.println("Current Fix Type: " + RTKSerial.Mode_Info());
    delay(10);
  if(rTK_Info() != RTK_Info::Time_Fix ){
    BLSERIAL.println("Wait Fix Value Before Proceed");
    }
  else{
    BLSERIAL.println("Fixed GPS Value");
    }
}
void RTK_Survey(){

  // Serial.print("Minimum_Observation_Time: ");Serial.print(RTKSerial.Minimum_Observation_Time_Info());Serial.println("[s]");
  // Serial.print("Required_Position_Accuracy: ");Serial.print(RTKSerial.Required_Position_Accuracy(), 4);Serial.println("[m]");
  // Serial.println("Current Fix Type: " + RTKSerial.Mode_Info()); 
  // Serial.println("Status: " + RTKSerial.Survey_Status());

  BLSERIAL.print("Minimum_Observation_Time: ");BLSERIAL.print(RTKSerial.Minimum_Observation_Time_Info());BLSERIAL.println("[s]");
  delay(10);
  BLSERIAL.print("Required_Position_Accuracy: ");BLSERIAL.print(RTKSerial.Required_Position_Accuracy(), 4);BLSERIAL.println("[m]");
  delay(10);
  Mode_Info();
  delay(10);
  BLSERIAL.println("Status: " + RTKSerial.Survey_Status());   
}
void RTK_Fixed(){
  
  // Serial.print("Latitude: ");Serial.print(RTKSerial.Latitude_Info(), 9);Serial.println("[deg]");
  // Serial.print("Longitude: ");Serial.print(RTKSerial.Longitude_Info(), 9);Serial.println("[deg]");
  // Serial.print("Altituded: ");Serial.print(RTKSerial.Altituded_Info(), 4);Serial.println("[m]");
  // Serial.print("Accuracy: ");Serial.print(RTKSerial.PositionAccuracy_Info(), 4);Serial.println("[m]");
  // Serial.println("Current Fix Type: " + RTKSerial.Mode_Info());

  BLSERIAL.print("Latitude: ");BLSERIAL.print(RTKSerial.Latitude_Info(), 9);BLSERIAL.println("[deg]");
  delay(10);
  BLSERIAL.print("Longitude: ");BLSERIAL.print(RTKSerial.Longitude_Info(), 9);BLSERIAL.println("[deg]");
  delay(10);
  BLSERIAL.print("Altituded: ");BLSERIAL.print(RTKSerial.Altituded_Info(), 4);BLSERIAL.println("[m]");
  delay(10);
  BLSERIAL.print("Accuracy: ");BLSERIAL.print(RTKSerial.PositionAccuracy_Info(), 4);BLSERIAL.println("[m]");
  delay(10);
  Mode_Info();
}
void RTK_Infomation(){

  // Serial.println("Current Rtk Mode: " + RTKSerial.Rtk_Mode_Info());
  BLSERIAL.println("Current Rtk Mode: " + RTKSerial.Rtk_Mode_Info());
  do {

    if (rTK_Mode() == RTK_Mode::Survey) {
      RTK_Survey();
      break;
    }
    else if(rTK_Mode() == RTK_Mode::Fixed_Mode){
      RTK_Fixed();
      break;
    }
    else{
      Interval_Connection++;
        BLSERIAL.println("Retry");
        delay(20);
        RTK_Infomation();
      if(Interval_Connection == 3){
        BLSERIAL.println("Not able to retrive data");
        delay(10);
        BLSERIAL.println("Retry");
        delay(20);
        RTK_Infomation();
        break;
      }
    }
   }while(1);
  Interval_Connection = 0;
}

void setup() {
  delay(5000);
	Serial.begin(115200);
  delay(1000);
  Serial.println("Program Start");
  delay(1000);
  BL_Connection();
  // RTKSerial.Survey_Mode_Info();
  // put your setup code here, to run once:
}

void loop() {
    
  if (BLSERIAL.available() > 0){//Check Bluetooth avai
    char incomingByte = BLSERIAL.read();//Read incoming char and ready to store
    readString += incomingByte; //makes the string readString
  }

  if (readString.length() >0){
  int lwn = readString.length();
  int first_comma = readString.indexOf(','); //Find the position of 1st comma 
  int second_comma = readString.indexOf(',', first_comma+1); //Find the position of 2nd comma 
  int third_comma = readString.indexOf(',', second_comma+1); //Find the position of 3rd comma
  int fourd_comma = readString.indexOf(',', third_comma+1); //Find the position of 3rd comma
  int fith_comma = readString.indexOf(',', fourd_comma+1); //Find the position of 3rd comma
  int six_comma = readString.indexOf(',', fith_comma+1); //Find the position of 3rd comma
  String Mode = "";    
  
  for(int i=0; i<first_comma ; i++){ //Values form 2nd comma to 3rd comma is Latitude 
    Mode = Mode + readString.charAt(i);
    Modes = Mode.toInt();
    switch (Modes){

      case 1:{
        
        BLSERIAL.println("Connecting Ebyte");
        RTKSERIAL.end();
        EB_Connection();
        
        String BRate = "";    
        for(int i=first_comma+1; i<second_comma; i++) //Values form 1nd comma to 2rd comma is Latitude 
        BRate = BRate + readString.charAt(i);
        uint8_t New_BaudRate = BRate.toInt();
        EBSerial.SetUARTBaudRate(New_BaudRate);
       
        String Addr = "";    
        for(int i=second_comma+1; i<third_comma; i++) //Values form 1nd comma to 2rd comma is Latitude 
        Addr = Addr + readString.charAt(i);
        uint16_t New_Address = Addr.toInt();
        EBSerial.SetAddress(New_Address);
        
        String Chnl = "";    
        for(int i=third_comma+1; i<lwn; i++) //Values form 1nd comma to 2rd comma is Latitude 
        Chnl = Chnl + readString.charAt(i);
        uint16_t New_Channel = Chnl.toInt();
        EBSerial.SetChannel(New_Channel);

        EBSerial.SaveParameters(); //stuck sini

        BLSERIAL.print("New Baud Rate: ");BLSERIAL.println(New_BaudRate);
        delay(10);
        BLSERIAL.print("New Address: ");BLSERIAL.println(New_Address);
        delay(10);
        BLSERIAL.print("New Channel: ");BLSERIAL.println(New_Channel);
        delay(10);


        EBSERIAL.end();
        
        
      }

      break;
      
      default:
        break;
      }
      
      readString="";
    }
  } 
}
// 