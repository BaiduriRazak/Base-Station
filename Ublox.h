#ifndef UBLOX_H
#define UBLOX_H
#include <Arduino.h> //Declared weak in Arduino.h to allow user redefinitions.
#include "EnumBoolen.h" //#include "Mm.h" For Enum Logic
#include "Debug.h" //#include "Mm.h" For Enum Logic

class Ublox  {
  // Class Member Variables
  // Constructor - creates a NRA15
  private:
    HardwareSerial* hwStream; //Pointer class HardwareSerial hwStream
    HardwareSerial* hwStream2; //Pointer class HardwareSerial hwStream2
    Flasher* led; //Pointer class Flasher Led
    int SensorPin1; // The number of the SensorPin
    int SensorPin2; // The number of the SensorPin

  public:
    Ublox( HardwareSerial& device,HardwareSerial& device2, Flasher& flasher)
    
    {hwStream = &device;
    hwStream2 = &device2;
    led = &flasher;
    } //Pass reference to Serial object into a class
    Ublox(int Pin,int Smin);
    void begin(uint32_t baudRate); //Void Function Parameter begin declaration
    uint8_t IncomingNewMessage(); //Void Function Parameter IncomingNewMessage declaration
    
    bool Is_Data_NR15_Event = false;  //bool Is_Data_NR15_Event declaration
};

#endif