#include "Debug.h"

Flasher::Flasher(int pin, long on, long off) {
  // Use 'this->' to make the difference between the
  // 'pin' attribute of the class and the 
  // local variable 'pin' created from the parameter.
    ledPin = pin;//Pointer the ledPin
    pinMode(ledPin, OUTPUT); // Attaches the pinMode on ledPin    
	  OnTime = on; //Pointer the OnTime
	  OffTime = off; //Pointer the OffTime
	  ledState = LOW; // ledState used to set the LED 
	  previousMillis = 0; 
}

void Flasher::Update(){
  // check to see if it's time to change the state of the LED
  unsigned long currentMillis = millis();//Get the current "time" (actually the number of milliseconds since the program started)
  if((ledState == HIGH) && (currentMillis - previousMillis >= OnTime)){ //Check whether the period has elapsed
    ledState = LOW;  // Turn it off
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(ledPin, ledState);  // Update the actual LED
  }
  else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime)){ //Check whether the period has elapsed
    ledState = HIGH;  // turn it on
    previousMillis = currentMillis;   // Remember the time
    digitalWrite(ledPin, ledState);	  // Update the actual LED
  }
}
void Flasher::On(){
  digitalWrite(ledPin, HIGH); // ledState used to set the LED
}
void Flasher::Stop(){
  digitalWrite(ledPin, LOW); // ledState used to set the LED
}


ButtState::ButtState(int pin, Flasher& flasher) {
  // Use 'this->' to make the difference between the
  // 'pin' attribute of the class and the 
  // local variable 'pin' created from the parameter.
  Bpin = pin; //Assign the pin local Bpin
  pinMode(Bpin, INPUT); // Attaches the pinMode on ledPin    
  led = &flasher; //led contains the address of flasher
}

void ButtState::Update(){
  unsigned long currentMillis = millis();//Get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis - PreviousMillis >= Next_Interval) { //Check whether the period has elapsed
    PreviousMillis = currentMillis; //IMPORTANT to save the start time of the current function.
    buttonState = digitalRead(Bpin); //Assign buttonState input from Bpin
    if (buttonState != lastButtonState){ // if the state has changed, increment the counter
      if (buttonState == HIGH) { // if the current state is HIGH then the button went from off to on:
      buttonPushCounter++; //Inreasing buttonPushCounter by 1
      } else {
                   // if the current state is LOW then the button went from on to off:
      }
    }
    // save the current state as the last state, for next time through the loop
    lastButtonState = buttonState;  
  } 
    /** Update Button State VALUE
    * @brief  Compare buttonPushCounter WITH MODULATION 2
    * @brief State of button press or not
    * @param if Update enum rover_Mode() = Rover_Mode::Active;
    * @param else Nothing Change
    * @brief State of button press or not
    * @brief rover_Mode() = Rover_Mode::Inactive; 
    */
  if (buttonPushCounter % 2 == 0) {
    led->Update(); // Update Led Button State
    rover_Mode() = Rover_Mode::Active;
  } 
  else {
    led->Stop(); // Stop Led Button State
    rover_Mode() = Rover_Mode::Inactive;
  }  
}

Switch::Switch(int pin, Flasher& flasher) {
  // Use 'this->' to make the difference between the
  // 'pin' attribute of the class and the 
  // local variable 'pin' created from the parameter.
  Bpin = pin; //Assign the pin local Bpin
  pinMode(Bpin, INPUT_PULLUP); // Attaches the pinMode on ledPin    
  led = &flasher; //led contains the address of flasher
}

void Switch::Update(){
  unsigned long currentMillis = millis();//Get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis - PreviousMillis >= Next_Interval) { //Check whether the period has elapsed
    PreviousMillis = currentMillis; //IMPORTANT to save the start time of the current function.
    //Serial.println(digitalRead(Bpin));
  if (digitalRead(Bpin) == HIGH) {
    switch_Button() = Switch_Button::On_State;
    led->On(); // Update Led Button State

  } else {
    // D7 pin is low due to pushbutton pressed
    switch_Button() = Switch_Button::Off_State;
    led->Stop(); // Update Led Button State

  } 
  } 

}

BL_State::BL_State(int pin) {
  // Use 'this->' to make the difference between the
  // 'pin' attribute of the class and the 
  // local variable 'pin' created from the parameter.
  Bpin = pin; //Assign the pin local Bpin
  pinMode(Bpin, INPUT_PULLUP); // Attaches the pinMode on ledPin    
  //led = &flasher; //led contains the address of flasher
}

void BL_State::Update(){
  unsigned long currentMillis = millis();//Get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis - PreviousMillis >= Next_Interval) { //Check whether the period has elapsed
    PreviousMillis = currentMillis; //IMPORTANT to save the start time of the current function.
    
    byte but = digitalRead (Bpin);
    if (butLst != but)  {
        butLst = but;
        bluetooth_State() = Bluetooth_State::Bl_Disconnected;
        //led->Stop(); // Update Led Button State
        msec = millis ();
    }
    if ( (millis() - msec) > Timeout)
        bluetooth_State() = Bluetooth_State::Bl_Connected;
        //led->On(); // Update Led Button State
    
  } 
}

