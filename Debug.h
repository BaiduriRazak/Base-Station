#ifndef MY_DEBUG_H
#define MY_DEBUG_H
#include <Arduino.h> //Declared weak in Arduino.h to allow user redefinitions.
#include <elapsedMillis.h>
#include "EnumBoolen.h" //#include "Mm.h" For Enum Logic
//ButtState Sw(4,LedBD);  //Class name ButtState 
class Flasher {
  
  private:
  int ledPin;      // The number of the LED pin
	unsigned long OnTime;     // milliseconds of on-time
	unsigned long OffTime;    // milliseconds of off-time
	// These maintain the current state
	int ledState;             		// ledState used to set the LED
	unsigned long previousMillis;  	// will store last time LED was updated
    
  public:
    Flasher(int pin, long on, long off);
    virtual void Update(); // Methods Update LED
    virtual void On(); // Methods Stop LED
    virtual void Stop(); // Methods Stop LED
};

class ButtState { 
    /** class ButtState
    * @brief  ButtState Sw(4,LedBD);
    * @brief  Sw.Update(); //Call Update button state
    * @brief  Class Member Variables
    * @brief Constructor - creates a ButtState
    */
  private:
    int Bpin;// The number of the LED pin
    // These maintain the current state
    int buttonPushCounter = 0;   // counter for the number of button presses
    int buttonState = 0;         // current state of the button
    int lastButtonState = 0;     // previous state of the button
    unsigned long PreviousMillis = 0; // will store last time Button state value 
    unsigned long Next_Interval = 100; // next interval to count
    Flasher* led; //Pointer class Flasher Led
    
  public:
    ButtState(int pin, Flasher& Flasher); //Pass reference to Serial object into a class
    void Update(); // Methods Update Button State
    
    
};
class Switch { 
    /** class ButtState
    * @brief  ButtState Sw(4,LedBD);
    * @brief  Sw.Update(); //Call Update button state
    * @brief  Class Member Variables
    * @brief Constructor - creates a ButtState
    */
  private:
    int Bpin;// The number of the LED pin
    // These maintain the current state
    int buttonPushCounter = 0;   // counter for the number of button presses
    int buttonState = 0;         // current state of the button
    int lastButtonState = 0;     // previous state of the button
    unsigned long PreviousMillis = 0; // will store last time Button state value 
    unsigned long Next_Interval = 10; // next interval to count
    Flasher* led; //Pointer class Flasher Led
    
  public:
    Switch(int pin, Flasher& Flasher); //Pass reference to Serial object into a class
    void Update(); // Methods Update Button State
    
    
};
class BL_State { 
    /** class ButtState
    * @brief  ButtState Sw(4,LedBD);
    * @brief  Sw.Update(); //Call Update button state
    * @brief  Class Member Variables
    * @brief Constructor - creates a ButtState
    */
  private:
    int Bpin;// The number of the LED pin
    // These maintain the current state
    int buttonPushCounter = 0;   // counter for the number of button presses
    int buttonState = 0;         // current state of the button
    int lastButtonState = 0;     // previous state of the button
    unsigned long PreviousMillis = 0; // will store last time Button state value 
    unsigned long Next_Interval = 10; // next interval to count
    const unsigned long Timeout = 1000;
    byte butLst;
    unsigned long msec;
    Flasher* led; //Pointer class Flasher Led
    
  public:
    BL_State(int pin); //Pass reference to Serial object into a class
    void Update(); // Methods Update Button State
    
    
};
#endif