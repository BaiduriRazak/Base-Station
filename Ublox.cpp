#include "Ublox.h"
extern unsigned long PORT_SENSOR_TIMEOUT_MS;
Ublox::Ublox(int Pin,int Smin) {
  SensorPin1 = Pin; //Pointer the SensorPin
  SensorPin2 = Smin; //Pointer the MinVal
  pinMode(SensorPin1, OUTPUT); // Attaches the pinMode on ledPin       
  pinMode(SensorPin2, OUTPUT); // Attaches the pinMode on ledPin      
}
uint8_t Ublox::IncomingNewMessage()//Incoming data from Sensor
{
    digitalWrite(SensorPin1, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(SensorPin2, LOW);    // turn the LED off by making the voltage LOW
    if (hwStream->available())
    hwStream2->write(hwStream->read());

  return 0;
}

void Ublox::begin(uint32_t baudRate)
{
  if (hwStream && hwStream2)
  {
    hwStream->begin(baudRate); //Set baudRate
    hwStream2->begin(baudRate); //Set baudRate
  }
}