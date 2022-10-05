#include "RTK.h"

/** Begin HardwareSerial
 * @brief ISFE_UBLOX_GPSnitialization HardwareSerial
 * @param hwStream Serial Number
 * @param baudRate Set to 115200
 * @return length of the message in bytes (excluding serial stream start sign)
 */
void RTK::begin_default(uint32_t baudRate){
  if (hwStream){
  do {
    Serial.println("RTK:trying 38400 baud");
    hwStream->begin(baudRate);
    Interval_Connection++;

    if (myGPS.begin(*hwStream) == true){
      rtk_State_Status_Default() = Rtk_State_Status_Default::Rtk_Connected_Succes_Default;
      break;
    } 
    
    delay(100);
    Serial.println("RTK:trying 115200 baud");
    hwStream->begin(115200);
    if(Interval_Connection == 5){
      Serial.println("Connection Fail After 5 Times Trial");
      rtk_State_Default() = Rtk_State_Default::Rtk_Disconnected_Default;
      rtk_State_Status_Default() = Rtk_State_Status_Default::Rtk_Disconnected_Unsucces_Default;
      break;
    }
    if (myGPS.begin(*hwStream) == true) {
        Serial.println("RTK:connected at 115200 baud, switching to 38400");
        myGPS.setSerialRate(38400);
        delay(100);
    } else {
        //myGPS.factoryReset();
        delay(2000); //Wait a bit before trying again to limit the Serial output
    }
  } while(1);
  Interval_Connection = 0;
  rtk_State_Default() = Rtk_State_Default::Rtk_Connected_Default;
  if(Rtk_Status_Connection_Default()){
  
  Serial.println("RTK serial connected");
  led->Update(); // Update Led MRA72
  myGPS.setUART1Output(COM_TYPE_RTCM3); //Set the UART port to output UBX only
  myGPS.setI2COutput(COM_TYPE_RTCM3); //Set the I2C port to output UBX only (turn off NMEA noise)
  delay(10);
  myGPS.saveConfiguration(); //Save the current settings to flash and BBR
  delay(10);
  myGPS.saveConfiguration(); //Save the current settings to flash and BBR
  uint8_t currentUART1Setting_rtcm3 = myGPS.getVal8(UBLOX_CFG_UART1INPROT_RTCM3X);
  if (currentUART1Setting_rtcm3 == 1){
    // Serial.println("COM_TYPE_RTCM3");
    rtk_Rtcm3() = Rtk_Rtcm3::Rtk_Connected__Rtcm3;
    }
  }
  else{
    // Serial.println("Not Succes After Few Trial");
    rtk_Rtcm3() = Rtk_Rtcm3::Rtk_Disconnected_Rtcm3;
  }
  }
}


void RTK::begin_config(uint32_t baudRate){
  if (hwStream){
  do {
    Serial.println("RTK:trying 115200 baud");
    hwStream->begin(baudRate);
    Interval_Connection++;

    if (myGPS.begin(*hwStream) == true){
      rtk_State_Status() = Rtk_State_Status::Rtk_Connected_Succes;
      break;
    } 
    
    delay(100);
    Serial.println("RTK:trying 38400 baud");
    hwStream->begin(38400);
    if(Interval_Connection == 5){
      Serial.println("Connection Fail After 5 Times Trial");
      rtk_State() = Rtk_State::Rtk_Disconnected;
      rtk_State_Status() = Rtk_State_Status::Rtk_Disconnected_Unsucces;
      break;
    }
    if (myGPS.begin(*hwStream) == true) {
        Serial.println("RTK:connected at 38400 baud, switching to 115200");
        myGPS.setSerialRate(115200);
        delay(100);
    } else {
        //myGPS.factoryReset();
        delay(2000); //Wait a bit before trying again to limit the Serial output
    }
  } while(1);
  Interval_Connection = 0;
  rtk_State() = Rtk_State::Rtk_Connected;
  if(Rtk_Status_Connection()){
  
  Serial.println("RTK serial connected");
  led->Update(); // Update Led MRA72
  myGPS.setUART1Output(COM_TYPE_UBX); //Set the UART port to output UBX only
  myGPS.setI2COutput(COM_TYPE_UBX); //Set the I2C port to output UBX only (turn off NMEA noise)
  delay(10);
  myGPS.saveConfiguration(); //Save the current settings to flash and BBR
  delay(10);
  myGPS.saveConfiguration(); //Save the current settings to flash and BBR
  }
  else{
    Serial.println("Not Succes After Few Trial");
  }
  // if(Rtk_Status_Connection() != true){
  //   Serial.println("Totaly fail");
  // }
  // bool response = true;
  // Read the settings from RAM (what the module is running right now, not BBR, Flash, or default)
  // uint8_t currentUART1Setting_ubx = myGPS.getVal8(UBLOX_CFG_UART1INPROT_UBX);
  // uint8_t currentUART1Setting_nmea = myGPS.getVal8(UBLOX_CFG_UART1INPROT_NMEA);
  // uint8_t currentUART1Setting_rtcm3 = myGPS.getVal8(UBLOX_CFG_UART1INPROT_RTCM3X);

  // Serial.print("currentUART1Setting_ubx: ");
  // Serial.println(currentUART1Setting_ubx);
  // Serial.print("currentUART1Setting_nmea: ");
  // Serial.println(currentUART1Setting_nmea);
  // Serial.print("currentUART1Setting_rtcm3: ");
  // Serial.println(currentUART1Setting_rtcm3);

  // if (currentUART1Setting_ubx == 0 || currentUART1Setting_nmea == 0)
  // {
  //   Serial.println("Updating UART1 configuration");

  //   //setVal sets the values for RAM, BBR, and Flash automatically so no .saveConfiguration() is needed
  //   response &= myGPS.setVal8(UBLOX_CFG_UART1INPROT_UBX, 1);    //Enable UBX on UART1 Input
  //   response &= myGPS.setVal8(UBLOX_CFG_UART1INPROT_NMEA, 1);   //Enable NMEA on UART1 Input
  //   response &= myGPS.setVal8(UBLOX_CFG_UART1INPROT_RTCM3X, 0); //Disable RTCM on UART1 Input

  //   if (response == false)
  //     Serial.println("SetVal failed");
  //   else
  //     Serial.println("SetVal succeeded");
  // }
  // else
  //   Serial.println("No port change needed");

  // myGPS.setUART1Output(COM_TYPE_UBX); //Set the UART port to output UBX only
  // myGPS.setI2COutput(COM_TYPE_UBX); //Set the I2C port to output UBX only (turn off NMEA noise)
  // myGPS.saveConfiguration(); //Save the current settings to flash and BBR
  // myGPS.saveConfiguration(); //Save the current settings to flash and BBR
  }
}
void RTK::end(uint32_t baudRate){
    hwStream->end();
    Serial.println("RTK serial disconnected");
    led->Stop(); // Update Led MRA72
}
String RTK::Mode_Info(){
  String Mode_Info="";
  byte FixType = myGPS.getFixType();//Get Tmode LongitudeHp
  //Serial.print("FixType: ");Serial.print(FixType);
  switch (FixType){
  case 0:
    //Serial.println("No Fix");
    Mode_Info=(String(FixType) + "-" + "No Fix");
    rTK_Info() = RTK_Info::No_Fix;
    break;
  case 1:
    //Serial.println("Dead Reckoning");
    Mode_Info=(String(FixType) + "-" + "Dead Reckoning");
    rTK_Info() = RTK_Info::Dead_Reckoning;
    break;
  case 2:
    //Serial.println("2D");
    Mode_Info=(String(FixType) + "-" + "2D");
    rTK_Info() = RTK_Info::Two_D;
    break;
  case 3:
    //Serial.println("3D");
    Mode_Info=(String(FixType) + "-" + "3D");
    rTK_Info() = RTK_Info::Three_D;
    break;
  case 4:
    //Serial.println("GNSS");
    Mode_Info=(String(FixType) + "-" + "GNSS");
    rTK_Info() = RTK_Info::GNSS;
    break;
  case 5:
    //Serial.println("Time Fix");
    Mode_Info=(String(FixType) + "-" + "Time Fix");
    rTK_Info() = RTK_Info::Time_Fix;
    break;

  default:
    break;
  
  }
  return Mode_Info;
}
String RTK::Rtk_Mode_Info(){
  String T_Mode_Info="";
  uint8_t T_Mode = myGPS.getVal8(0x20030001,VAL_LAYER_RAM, 5000 ); //Get Tmode position mode
  switch (T_Mode){
  case 0:
  {
    //Serial.println("Disable");
    T_Mode_Info=(String(T_Mode) + "-" + "Disable");
    rTK_Mode() = RTK_Mode::Disable_Mode;
    }
    break;
    
  case 1:
    //Serial.println("Survey");
    T_Mode_Info=(String(T_Mode) + "-" + "Survey");
    rTK_Mode() = RTK_Mode::Survey;
    break;
  case 2: 
    //Serial.println("Fixed Mode");
    // String Fixed_Mode_RTK_Info2 = RTK::Fixed_Mode_RTK_Info();
    T_Mode_Info=(String(T_Mode) + "-" + "Fixed Mode");
    rTK_Mode() = RTK_Mode::Fixed_Mode;
    break;
  
  default:
    break;
  
  }
  return T_Mode_Info;
}
String RTK::Survey_Status(){
  String Servey_Status_Val="";
  
  int8_t Servey_Status = myGPS.getSurveyStatus(1000);//Get Tmode LongitudeHp
  //  Serial.print("SurveyStatus: ");Serial.print(Servey_Status);
  
  switch (Servey_Status){
  case 0:
  {
    //Serial.println("Disable");
    Servey_Status_Val=("In Progress");
    // rTK_Mode() = RTK_Mode::Disable_Mode;
    }
    break;
    
  case 1:
    Servey_Status_Val=("Successfully");
    int flag=+1 ;
    break;

  }
  return Servey_Status_Val;
}

String RTK::Survey_Mode_RTK_info(){
    int8_t Minimum_Observation_Time = myGPS.getVal32(0x40030010,VAL_LAYER_RAM, 2000 ); //Get Tmode position mode
    int32_t Required_Position_Accuracy = myGPS.getVal32(0x40030011,VAL_LAYER_RAM, 2000 ); //Get Tmode position mode
    d_rps = ((double)Required_Position_Accuracy) / 10000; // Now add the high resolution component (degrees * 10^-9 )
    String Survey_Return=("Minimum_Observation_Time: " + String(Minimum_Observation_Time) + "[s]" + + "\n" + + "Required_Position_Accuracy: " + String(d_rps, 4) + "[m]"+ +"\n" + + "Status: " + RTK::Survey_Status());// Return value through Bluetooth for mode 2
    return Survey_Return;
} 

int16_t RTK::Minimum_Observation_Time_Info(){
  int32_t Minimum_Observation_Time;
  do {
    Minimum_Observation_Time = myGPS.getVal32(0x40030010,VAL_LAYER_RAM, 2000 ); //Get Tmode position mode
    delay(10);
    if (Minimum_Observation_Time != 0){
    break;
    } 
  } while(1);
  //d_mot = ((double)Minimum_Observation_Time) / 10000; // Now add the high resolution component (degrees * 10^-9 )

  return Minimum_Observation_Time;
}
double RTK::Required_Position_Accuracy(){
  int32_t Required_Position_Accuracy;
  do {
    Required_Position_Accuracy = myGPS.getVal32(0x40030011,VAL_LAYER_RAM, 2000 ); //Get Tmode position mode
    delay(10);
    if (Required_Position_Accuracy != 0){
    break;
    } 
  } while(1);
  
  d_rps = ((double)Required_Position_Accuracy) / 10000; // Now add the high resolution component (degrees * 10^-9 )
  return d_rps;
} 
double RTK::Latitude_Info(){
  latitude = myGPS.getHighResLatitude();//Get Tmode Latitude
  latitudeHp = myGPS.getHighResLatitudeHp();//Get Tmode LatitudeHp
  d_lat = ((double)latitude) / 10000000.0; // Convert latitude from degrees * 10^-7 to degrees
  d_lat += ((double)latitudeHp) / 1000000000.0; // Now add the high resolution component (degrees * 10^-9 )
  return d_lat;
}
double RTK::Longitude_Info(){
  longitude = myGPS.getHighResLongitude();//Get Tmode Longitude
  longitudeHp = myGPS.getHighResLongitudeHp();//Get Tmode LongitudeHp
  d_lon = ((double)longitude) / 10000000.0; // Convert longitude from degrees * 10^-7 to degrees
  d_lon += ((double)longitudeHp) / 1000000000.0; // Now add the high resolution component (degrees * 10^-9 )
  return d_lon;
}
double RTK::Altituded_Info(){
  altituded = myGPS.getAltitude();//Get Tmode Altitude
  // delay(100);//delay
  d_alt = ((double)altituded) / 1000; // Now add the high resolution component (degrees * 10^-9 )
  return d_alt;
}
double RTK::PositionAccuracy_Info(){
  positionaccuracy = myGPS.getPositionAccuracy();//Get Tmode LongitudeHp
  d_acc = ((double)positionaccuracy) / 1000; // Now add the high resolution component (degrees * 10^-9 )
  return d_acc;
}

void RTK::Fixed_Mode_RTK_Change(){
  // String Fixed_Return="";
  // String Fixed_Retrive="";
  // String Final_Return="";
  // latitude = myGPS.getHighResLatitude();//Get Tmode Latitude
  // latitudeHp = myGPS.getHighResLatitudeHp();//Get Tmode LatitudeHp
  // longitude = myGPS.getHighResLongitude();//Get Tmode Longitude
  // longitudeHp = myGPS.getHighResLongitudeHp();//Get Tmode LongitudeHp
  // altituded = myGPS.getAltitude();//Get Tmode Altitude
  // positionaccuracy = myGPS.getPositionAccuracy();//Get Tmode LongitudeHp
  // Serial.print("altituded: ");Serial.print(altituded);
  // Serial.print("  ");
  // Serial.print("positionaccuracy: ");Serial.println(positionaccuracy);
  int32_t altituded2 = altituded/10;
  int32_t positionaccuracy2 = positionaccuracy*10;
  // Serial.print("altituded2: ");Serial.print(altituded2);
  // Serial.print("  ");
  // Serial.print("positionaccuracy2: ");Serial.println(positionaccuracy2);
  delay(100);
  myGPS.setVal32(0x20030001, 2, VAL_LAYER_RAM);//Set Tmode3 to Fix Mode
  delay(100);//delay
  myGPS.setVal32(0x20030002, 1, VAL_LAYER_RAM);//Set Tmode3 to Correct degree mode
  delay(100);//delay
  myGPS.setVal32(0x40030009, latitude, VAL_LAYER_RAM);//Set Tmode3 Latitude
  myGPS.setVal32(0x4003000A, longitude, VAL_LAYER_RAM);//Set Tmode3 Longitude
  myGPS.setVal32(0x2003000C, latitudeHp, VAL_LAYER_RAM);//Set Tmode3 LatitudeHp
  myGPS.setVal32(0x2003000D, longitudeHp, VAL_LAYER_RAM);//Set Tmode3 LongitudeHp
  myGPS.setVal32(0x4003000B, altituded2, VAL_LAYER_RAM);//Set Tmode3 Altitude
  myGPS.setVal32(0x4003000F, positionaccuracy2, VAL_LAYER_RAM);//Set Tmode3 Accuracy
  delay(100);//delay
  myGPS.saveConfiguration(); //Save the current settings to flash and BBR
  delay(100);//delay
  myGPS.saveConfiguration(); //Save the current settings to flash and BBR
  delay(100);//delay
  myGPS.saveConfiguration(); //Save the current settings to flash and BBR
  // delay(1000);//delay
  // int32_t latitude2 = myGPS.getHighResLatitude();//Get Tmode Latitude
  // int8_t latitudeHp2 = myGPS.getHighResLatitudeHp();//Get Tmode LatitudeHp
  // int32_t longitude2 = myGPS.getHighResLongitude();//Get Tmode Longitude
  // int8_t longitudeHp2 = myGPS.getHighResLongitudeHp();//Get Tmode LongitudeHp
  // int32_t altituded2 = myGPS.getAltitude();//Get Tmode Altitude
  // uint32_t  positionaccuracy2 = myGPS.getPositionAccuracy();//Get Tmode LongitudeHp
  // Serial.println("After :::");
  // Serial.print("latitude: ");Serial.print(latitude2);
  // Serial.print("  ");
  // Serial.print("latitudeHp: ");Serial.print(latitudeHp2);
  // Serial.print("  ");
  // Serial.print("longitude: ");Serial.print(longitude2);
  // Serial.print("  ");
  // Serial.print("longitudeHp: ");Serial.print(longitudeHp2);
  // Serial.print("  ");
  // Serial.print("altituded: ");Serial.print(altituded2);
  // Serial.print("  ");
  // Serial.print("positionaccuracy: ");Serial.println(positionaccuracy2);

}

void RTK::Servey_Mode_RTK(int32_t Observation_Time, int32_t Pos_Acc){
    myGPS.setVal32(0x20030001, 1, VAL_LAYER_RAM);//Set Tmode3 to Survey mode
    delay(100);
    myGPS.setVal32(0x40030010, Observation_Time, VAL_LAYER_RAM);//Set Tmode3 Observation_Time
    delay(100);
    myGPS.setVal32(0x40030011, Pos_Acc, VAL_LAYER_RAM);//Set Tmode3 Pos_Acc
    delay(100);
    myGPS.saveConfiguration(); //Save the current settings to flash and BBR
    delay(100);
    myGPS.saveConfiguration(); //Save the current settings to flash and BBR  
    delay(100);
    myGPS.saveConfiguration(); //Save the current settings to flash and BBR
} 
String RTK::Fixed_Mode_RTK(int32_t Latitude, int32_t Longitude, int32_t Altituded, int32_t Accuracy, int8_t Latitude_Hp, int8_t Longitude_Hp){
  
  myGPS.setVal32(0x20030001, 2, VAL_LAYER_RAM);//Set Tmode3 to Fix Mode
  delay(100);//delay
  myGPS.setVal32(0x20030002, 1, VAL_LAYER_RAM);//Set Tmode3 to Correct degree mode
  delay(200);//delay
  myGPS.setVal32(0x40030009, Latitude, VAL_LAYER_RAM);//Set Tmode3 Latitude
  myGPS.setVal32(0x4003000A, Longitude, VAL_LAYER_RAM);//Set Tmode3 Longitude
  myGPS.setVal32(0x2003000C, Latitude_Hp, VAL_LAYER_RAM);//Set Tmode3 LatitudeHp
  myGPS.setVal32(0x2003000D, Longitude_Hp, VAL_LAYER_RAM);//Set Tmode3 LongitudeHp
  myGPS.setVal32(0x4003000B, Altituded, VAL_LAYER_RAM);//Set Tmode3 Altitude
  myGPS.setVal32(0x4003000F, Accuracy, VAL_LAYER_RAM);//Set Tmode3 Accuracy
  myGPS.saveConfiguration(); //Save the current settings to flash and BBR
  delay(100);//delay
  int32_t latitude = myGPS.getHighResLatitude();//Get Tmode Latitude
  int8_t latitudeHp = myGPS.getHighResLatitudeHp();//Get Tmode LatitudeHp
  int32_t longitude = myGPS.getHighResLongitude();//Get Tmode Longitude
  int8_t longitudeHp = myGPS.getHighResLongitudeHp();//Get Tmode LongitudeHp
  int32_t altituded = myGPS.getAltitude();//Get Tmode Altitude
  delay(100);//delay
  double d_lat; // latitude Defines storage for the lat and lon as double
  double d_lon; // longitude Defines storage for the lat and lon as double
  double d_alt; // longitude Defines storage for the lat and lon as double
  d_lat = ((double)latitude) / 10000000.0; // Convert latitude from degrees * 10^-7 to degrees
  d_lat += ((double)latitudeHp) / 1000000000.0; // Now add the high resolution component (degrees * 10^-9 )
  d_lon = ((double)longitude) / 10000000.0; // Convert longitude from degrees * 10^-7 to degrees
  d_lon += ((double)longitudeHp) / 1000000000.0; // Now add the high resolution component (degrees * 10^-9 )
  d_alt = ((double)altituded) / 1000; // Now add the high resolution component (degrees * 10^-9 )
  String Fixed_Return=(String(d_lat, 9) + "," + String(d_lon, 9)+ "," + String(d_alt, 4));// Return value through Bluetooth for mode 2
  // Serial.println("Fixed_Mode_RTK");
  // resent_BL()= Resent_BL::Fixed_Mode_Resent;
  return Fixed_Return;
}

int8_t RTK::Reset_RTK(){

  int32_t Latitude= 32583043, Longitude = 1014969581, Altituded = 4440, Accuracy= 5000;
  int8_t Latitude_Hp = 36, Longitude_Hp=16;
  myGPS.setVal32(0x20030001, 2, VAL_LAYER_RAM);//Set Tmode3 to Fix Mode
  myGPS.setVal32(0x20030002, 1, VAL_LAYER_RAM);//Set Tmode3 to Correct degree mode
  myGPS.setVal32(0x40030009, Latitude, VAL_LAYER_RAM);//Set Tmode3 Latitude
  myGPS.setVal32(0x2003000C, Latitude_Hp, VAL_LAYER_RAM);//Set Tmode3 LatitudeHp
  myGPS.setVal32(0x4003000A, Longitude, VAL_LAYER_RAM);//Set Tmode3 Longitude
  myGPS.setVal32(0x2003000D, Longitude_Hp, VAL_LAYER_RAM);//Set Tmode3 LongitudeHp
  myGPS.setVal32(0x4003000B, Altituded, VAL_LAYER_RAM);//Set Tmode3 Altitude
  myGPS.setVal32(0x4003000F, Accuracy, VAL_LAYER_RAM);//Set Tmode3 Accuracy
  myGPS.saveConfiguration(); //Save the current settings to flash and BBR
  Serial.println("Reset_Configuration");
  int8_t Surwey = myGPS.getVal8(0x20030002,VAL_LAYER_RAM, 250 ); //Get Tmode position mode

  //resent_BL()= Resent_BL::Rst_Firmware_Resent;
  return Surwey;
}
void RTK::Hard_Reset_RTK(){

  
  myGPS.hardReset();
  Serial.println("Hard_Reset_RTK");
  myGPS.saveConfiguration(); //Save the current settings to flash and BBR
 


  
}
// void RTK::Configuration(){
// if(rTK_State()==RTK_State::Rst_Firmware){
//   Reset_RTK();
//   rTK_State() = RTK_State::Disable;
//   base_Mode() = Base_Mode::Bl_Mode;
// }
// else if(rTK_State()==RTK_State::Servey_Mode){
//   //Servey_Mode_RTK();
//   rTK_State() = RTK_State::Disable;
//   base_Mode() = Base_Mode::Bl_Mode;
// }
// else if(rTK_State()==RTK_State::Fixed_Mode){
//   //Fixed_Mode_RTK();
//   rTK_State() = RTK_State::Disable;
//   base_Mode() = Base_Mode::Bl_Mode;
// }
// else if(rTK_State()==RTK_State::Add_Mode){
  
// }
// }
  // uint8_t  SurveyStatus = myGPS.getSurveyStatus(1000);//Get Tmode LongitudeHp
  // Serial.print("SurveyStatus: ");Serial.print(SurveyStatus);
  // Serial.print("  ");
  // delay(100);//delay
  // // byte fixType = myGPS.getFixType();
  // byte FixType = myGPS.getFixType();//Get Tmode LongitudeHp
  // Serial.print("FixType: ");Serial.print(FixType);
  // Serial.print("  ");
  // delay(100);//delay
// delay(100);//delay
  // Serial.print("T_Mode: ");Serial.print(T_Mode);
  // Serial.println("  ");
  // byte  CarrierSolutionType = myGPS.getCarrierSolutionType();//Get Tmode LongitudeHp
  // Serial.print("CarrierSolutionType: ");Serial.print(CarrierSolutionType);
  // Serial.println("  ");
  // uint8_t  PositionAccuracy = myGPS.getPositionAccuracy(1000);//Get Tmode LongitudeHp
  // Serial.print("PositionAccuracy: ");Serial.print(PositionAccuracy);
  // Serial.print("  ");
  // int32_t Minimum_Observation_Time = myGPS.getVal32(0x40030010,VAL_LAYER_RAM, 1000 ); //Get Tmode position mode
  // Serial.print("Minimum_Observation_Time: ");Serial.print(Minimum_Observation_Time);
  // Serial.print("  ");
  // int32_t Required_Position_Accuracy = myGPS.getVal32(0x40030011,VAL_LAYER_RAM, 1000 ); //Get Tmode position mode
  // Serial.print("Required_Position_Accuracy: ");Serial.print(Required_Position_Accuracy);