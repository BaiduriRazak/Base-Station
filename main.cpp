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
HardwareSerial BLSERIAL(PA10, PA9);//#define RTKSERIAL Serial1 RX:TX(31,30)
HardwareSerial RTKSERIAL(PA3, PA2); //#define EYBTESERIAL Serial2 RX:TX(13,12) 
BL_State Bl_Con(PB15);  //class ButtState
EBYTE EBSERIAL (RTKSERIAL, PB0, PB1);
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
  
  
  // while(!Serial){};
  

  delay(1000);
  Serial.println("Program Start");
  // RTKSerial.Survey_Mode_Info();
  // put your setup code here, to run once:
}

void loop() {
  LedBD.Update();
  Bl_Con.Update();
  if(bluetooth_State() == Bluetooth_State::Bl_Connected){
    if (bluetooth_State() == Bluetooth_State::Bl_Connected && interval_State() == Interval_State::Interval_In){
      LedBL.On();
      BL_Connection();
      Serial.println("Connection Establish With Base Station");
      BLSERIAL.println("Connection Establish With Base Station");
      RTK_Connection_Configuration();
      if(Rtk_Status_Connection()){
      BLSERIAL.println("Connection Establish With RTK");
      delay(1000);
      RTK_Infomation();
      delay(1000); 
      BL_Connection(); 
        }
      else{
      BLSERIAL.println("Connection Fail After Few Trial");
      BLSERIAL.println("Please Reboot System");
      }

      interval_State() = Interval_State::Interval_out;
      }
  }
  else{
  // if (bluetooth_State() == Bluetooth_State::Bl_Disconnected && interval_State2() == Interval_State2::Interval_In2){
  //     Serial.println("Disconnection Establish With Base Station");
  //     // RTK_Connection_Configuration();
  //     interval_State2() = Interval_State2::Interval_out2;
  //   }
    interval_State() = Interval_State::Interval_In;
    LedBL.Stop();
    //RTK_Connection_Configuration();
  }

  // LedRTK.Update();
  // LedBL.Update();
  // put your main code here, to run repeatedly:
  while (BLSERIAL.available()){//Check Bluetooth available
  unsigned long currentMillis = millis(); //Get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis - PreviousMillis_BL >= Next_Interval_BL){//Check whether the period has elapsed
    PreviousMillis_BL = currentMillis;//IMPORTANT to save the start time of the current function.
    if (BLSERIAL.available() > 0){//Check Bluetooth avai
      char incomingByte = BLSERIAL.read();//Read incoming char and ready to store
      readString += incomingByte; //makes the string readString
    }
  } 
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
        String Ob_T = "";    
        for(int i=first_comma+1; i<second_comma; i++) //Values form 1nd comma to 2rd comma is Latitude 
        Ob_T = Ob_T + readString.charAt(i);
        int32_t Observation_Time = Ob_T.toInt();
        String Pos = "";    
        for(int i=second_comma+1;  i<lwn; i++)//Values form 2nd comma to 3rd comma is Latitude 
        Pos = Pos + readString.charAt(i);
        int32_t Pos_Acc = Pos.toInt();
        // Serial.println("Parameter Set: ");
        // delay(10);
        // Serial.print("Observation_Time: "); Serial.print(Observation_Time);;Serial.println("[s]");
        // // delay(10);
        // Serial.print("Pos_Acc: ");Serial.print(Pos_Acc);;Serial.println("[m]");
        BLSERIAL.println("Parameter Set: ");
        delay(10);
        BLSERIAL.print("Observation_Time: ");BLSERIAL.print(Observation_Time);BLSERIAL.println("[s]"); 
        delay(10);
        BLSERIAL.print("Pos_Acc: ");BLSERIAL.print(Pos_Acc);BLSERIAL.println("[m]");
        int TemMOT = RTKSerial.Minimum_Observation_Time_Info();
        delay(10);
        int TemRPA = RTKSerial.Required_Position_Accuracy()*10000;
        BLSERIAL.println("Old Parameter: ");
        delay(10);
        BLSERIAL.print("Observation_Time: ");BLSERIAL.print(TemMOT);BLSERIAL.println("[s]"); 
        delay(10);
        BLSERIAL.print("Pos_Acc: ");BLSERIAL.print(TemRPA);BLSERIAL.println("[m]");

        // Serial.print("Observation_Time: "); Serial.print(TemMOT);;Serial.println("[s]");
        // Serial.print("Pos_Acc: ");Serial.print(TemRPA);;Serial.println("[m]");
        // Serial.println(TemVal);
        if(TemMOT == Observation_Time && TemRPA == Pos_Acc){
          BLSERIAL.println("Same Value As Current Settings");
        }
        else{
          BLSERIAL.println("Value Change");
          delay(10);
          RTKSerial.Servey_Mode_RTK(Observation_Time,Pos_Acc);
          BLSERIAL.println("New Settings");
          delay(100);
          RTK_Infomation();
          delay(100);
        }
        //RTK_Infomation();
        //BLSERIAL.println(String(Modes) + "," + String(Surwey));// Return value through Bluetooth for mode 1
      }
        break;
      
      case 2:{
        String Latt = "";    
        for(int i=first_comma+1; i<second_comma; i++) //Values form 1nd comma to 2rd comma is Latitude 
        Latt = Latt + readString.charAt(i);
        int32_t Latitude = Latt.toInt();
        String Lonn = "";    
        for(int i=second_comma+1; i<third_comma; i++)//Values form 2nd comma to 3rd comma is Latitude 
        Lonn = Lonn + readString.charAt(i);
        int32_t Longitude = Lonn.toInt();
        String Attt = "";  
        for(int i=third_comma+1; i<fourd_comma; i++)//Values form 3nd comma to 4rd comma is Latitude 
        Attt = Attt + readString.charAt(i);
        int32_t Altituded = Attt.toInt();
        String Accc = "";  
        for(int i=fourd_comma+1; i<fith_comma; i++) //Values form 4nd comma to 5rd comma is Latitude 
        Accc = Accc + readString.charAt(i);
        int32_t Accuracy = Accc.toInt();
        String Latt_Hp = "";  
        for(int i=fith_comma+1; i<six_comma; i++) //Values form 5nd comma to 6rd comma is Latitude 
        Latt_Hp = Latt_Hp + readString.charAt(i);
        int8_t Latitude_Hp = Latt_Hp.toInt();
        String Lonn_Hp = "";  
        for(int i=six_comma+1; i<lwn; i++) //Values form 6nd comma to 7rd comma is Latitude 
        Lonn_Hp = Lonn_Hp + readString.charAt(i);
        int8_t Longitude_Hp = Lonn_Hp.toInt();
        Serial.print("Lat: "); Serial.print(Latitude);Serial.print(" Lon: ");Serial.print(Longitude);
        Serial.print(" Att: "); Serial.print(Altituded);Serial.print(" Acc: ");Serial.print(Accuracy);
        Serial.print(" Lat_Hp: "); Serial.print(Latitude_Hp);Serial.print(" Lon_Hp: ");Serial.println(Longitude_Hp);
        String Fixed_Return =RTKSerial.Fixed_Mode_RTK(Latitude,Longitude,Altituded,Accuracy,Latitude_Hp,Longitude_Hp);
        BLSERIAL.println(String(Modes) + "," + Fixed_Return);// Return value through Bluetooth for mode 1
      }
        break;
      case 3:{
        String Vall = "";    
        for(int i=first_comma+1; i<lwn; i++) //Values form 1nd comma to 2rd comma is Latitude 
        Vall = Vall + readString.charAt(i);
        int Value = Vall.toInt();
        switch (Value)
        {
        case 1:
          Serial.println("Current Rtk Mode");
          BLSERIAL.println("Current Rtk Mode");
          RTK_Connection_Configuration();
          if(Rtk_Status_Connection()){
          BLSERIAL.println("Connection Establish With RTK");
          delay(100);
          RTK_Infomation();
          delay(100); 
          BL_Connection(); 
            }
          else{
          BLSERIAL.println("Connection Fail After Few Trial");
          BLSERIAL.println("Please Reboot System");
          }
          break;
        case 2:
          RTKSerial.Hard_Reset_RTK();
          BLSERIAL.println("Hard_Reset_RTK");
          break;
        
        default:
          break;
        }
        // String Fixed_Return =RTKSerial.Survey_Mode_Info();
        // BLSERIAL.println(String(Modes) + "," + Fixed_Return);

      }
        break;
      case 4:{
        String Vall = "";    
        for(int i=first_comma+1; i<lwn; i++) //Values form 1nd comma to 2rd comma is Latitude 
        Vall = Vall + readString.charAt(i);
        int Value = Vall.toInt();
        switch (Value)
        {
        case 1:
           Serial.println("GPS_Information ");
           BLSERIAL.println("GPS_Information ");
           RTK_Fixed();
          //  Serial.println(RTKSerial.Fixed_Mode_RTK_Info());
          //  BLSERIAL.println("Survey_Mode_Information ");
          //  BLSERIAL.println(RTKSerial.Fixed_Mode_RTK_Info());
          break;
        case 2:
           Serial.println("Survey_Mode_Information ");
           RTK_Fixed();
           delay(100);
           RTKSerial.Fixed_Mode_RTK_Change();
           delay(100);
           RTK_Infomation();
          // Serial.println(RTKSerial.Fixed_Mode_RTK_Change());
          //  BLSERIAL.println("Survey_Mode_Information ");
          //  BLSERIAL.println(RTKSerial.Fixed_Mode_RTK_Change());
          break;
        
        default:
          break;
        }
        // String Fixed_Return =RTKSerial.Survey_Mode_Info();
        // BLSERIAL.println(String(Modes) + "," + Fixed_Return);

      }
        break;
      case 5:{
        String Vall = "";    
        for(int i=first_comma+1; i<lwn; i++) //Values form 1nd comma to 2rd comma is Latitude 
        Vall = Vall + readString.charAt(i);
        int Value = Vall.toInt();
        switch (Value)
        {
        case 1:
           Serial.println("Set to Default Setting ");
           BLSERIAL.println("Set to Default Setting ");
           RTK_Connection_Default();
           if(rtk_Rtcm3() == Rtk_Rtcm3::Rtk_Connected__Rtcm3){
             BLSERIAL.println("Set to Default RTCM3 ");

           }
           else{
             BLSERIAL.println("Fail set to Default RTCM3 ");
           }
          //  RTK_Fixed();
          //  Serial.println(RTKSerial.Fixed_Mode_RTK_Info());
          //  BLSERIAL.println("Survey_Mode_Information ");
          //  BLSERIAL.println(RTKSerial.Fixed_Mode_RTK_Info());
          break;
        case 2:
        if (RTKSerial.Reset_RTK() == 1 ){
          BLSERIAL.println(String(Modes) + ",4" );
        }
        else{
          BLSERIAL.println(String(Modes) + ",5" );
        }
          break;
        
        default:
          break;
        }
  
      }
        break;

      case 6:{
        
        EBSERIAL.SetMode(MODE_PROGRAM);
                   
        String BRate = "";    
        for(int i=first_comma+1; i<second_comma; i++) //Values form 1nd comma to 2rd comma is Latitude 
        BRate = BRate + readString.charAt(i);
        uint8_t Baud_Rate = BRate.toInt();
        EBSERIAL.SetUARTBaudRate(Baud_Rate);
        //EBSERIAL.SaveParameters();

        String Addr = "";    
        for(int i=second_comma+1; i<third_comma; i++) //Values form 1nd comma to 2rd comma is Latitude 
        Addr = Addr + readString.charAt(i);
        uint16_t New_Address = Addr.toInt();
        EBSERIAL.SetAddress(New_Address);
        //EBSERIAL.SaveParameters();

        String Chnl = "";    
        for(int i=third_comma+1; i<lwn; i++) //Values form 1nd comma to 2rd comma is Latitude 
        Chnl = Chnl + readString.charAt(i);
        uint16_t New_Channel = Chnl.toInt();
        EBSERIAL.SetChannel(New_Channel);
        //EBSERIAL.SaveParameters();

        EBSERIAL.SetMode(MODE_NORMAL);

        BLSERIAL.print("New Baud Rate");BLSERIAL.println(Baud_Rate);
        delay(10);
        BLSERIAL.print("New Address");BLSERIAL.println(New_Address);
        delay(10);
        BLSERIAL.print("New Channel");BLSERIAL.println(New_Channel);
        delay(10);
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