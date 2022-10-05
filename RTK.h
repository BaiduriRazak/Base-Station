#ifndef RTK_H
#define RTK_H

#include <Arduino.h> //Declared weak in Arduino.h to allow user redefinitions.
#include "EnumBoolen.h" //#include "Mm.h" For Enum Logic
#include "Debug.h" //#include "Mm.h" For Enum Logic
#include "SparkFun_Ublox_Arduino_Library.h" //#include "common/mavlink_msg_request_data_stream.h"


class RTK{
    // Class Member Variables
    // Constructor - creates a MR72
  private:
    HardwareSerial* hwStream; //Pointer class HardwareSerial hwStream
    Flasher* led; //Pointer class Flasher Led
    
    unsigned long Timer= 10;;     // milliseconds of on-time
	  unsigned long previousMillis;  	// will store last time Timer was updated
    

  public:

    int flag = 0;
    RTK( HardwareSerial& device, Flasher& flasher) {
      hwStream = &device;
      led = &flasher;
    }//Pass reference to Serial object into a class
    
    SFE_UBLOX_GPS myGPS;
    void begin_config(uint32_t baudRate); //Void Function Parameter begin declaration
    void begin_default(uint32_t baudRate); //Void Function Parameter begin declaration
    void end(uint32_t baudRate); //Void Function Parameter begin declaration
    String Rtk_Mode_Info();
    String Mode_Info();
    String Survey_Mode_RTK_info();
    int16_t Minimum_Observation_Time_Info();
    void Fixed_Mode_RTK_Change();
    void Hard_Reset_RTK();
    double Latitude_Info();
    double Longitude_Info();
    double Altituded_Info();
    double PositionAccuracy_Info();
    double Required_Position_Accuracy();
    String Survey_Status();

    void Servey_Mode_RTK(int32_t Observation_Time, int32_t Pos_Acc);
    String Fixed_Mode_RTK(int32_t Lat, int32_t Lon, int32_t Att, int32_t Acc, int8_t Lat_Hp, int8_t Lon_Hp);
    int8_t Reset_RTK();
    void Configuration();
   
    //#Variable configuration#//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //#######################
    int32_t latitude;
    int8_t latitudeHp;
    int32_t longitude;
    int8_t longitudeHp;
    int32_t altituded;
    uint32_t  positionaccuracy;
    long Interval_Connection = 0;
    double d_lat; // latitude Defines storage for the lat and lon as double
    double d_lon; // longitude Defines storage for the lat and lon as double
    double d_alt; // longitude Defines storage for the lat and lon as double
    double d_acc; // longitude Defines storage for the lat and lon as double
    double d_mot; // longitude Defines storage for the lat and lon as double
    double d_rps; // longitude Defines storage for the lat and lon as double
    //#Boolen configuration#//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //#######################
    bool Is_Data_RTK_Event = false; //bool Is_Data_MRA72_Event declaration
};

#endif