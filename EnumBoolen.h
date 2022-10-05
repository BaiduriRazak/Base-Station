#ifndef ENUMBOOLEN_H
#define ENUMBOOLEN_H
#include <Arduino.h>


enum Switch_Button {
  Off_State,
  On_State, // GPS detected
};
//  extern enum Obs_State obsState;
inline Switch_Button& switch_Button() {
  static Switch_Button currentswitch_Button;
  return currentswitch_Button;
}
enum Rtk_State_Default {
  Rtk_Disconnected_Default,
  Rtk_Connected_Default, // GPS detected
};
//  extern enum Obs_State obsState;
inline Rtk_State_Default& rtk_State_Default() {
  static Rtk_State_Default currentrtk_State_Default;
  return currentrtk_State_Default;
}


enum Rtk_Rtcm3 {
  Rtk_Disconnected_Rtcm3,
  Rtk_Connected__Rtcm3, // GPS detected
};
//  extern enum Obs_State obsState;
inline Rtk_Rtcm3& rtk_Rtcm3() {
  static Rtk_Rtcm3 currentrtk_Rtk_Rtcm3;
  return currentrtk_Rtk_Rtcm3;
}

enum Rtk_State_Status_Default {
  Rtk_Disconnected_Unsucces_Default,
  Rtk_Connected_Succes_Default, // GPS detected
};
//  extern enum Obs_State obsState;
inline Rtk_State_Status_Default& rtk_State_Status_Default() {
  static Rtk_State_Status_Default currentrtk_State_Status_Default;
  return currentrtk_State_Status_Default;
}
inline bool Rtk_Status_Connection_Default() {
  if ((rtk_State_Default() == Rtk_State_Default::Rtk_Connected_Default && rtk_State_Status_Default() == Rtk_State_Status_Default::Rtk_Connected_Succes_Default )) {
    return true;
  }
  return false;
}
enum Rtk_State {
  Rtk_Disconnected,
  Rtk_Connected, // GPS detected
};
//  extern enum Obs_State obsState;
inline Rtk_State& rtk_State() {
  static Rtk_State currentrtk_State;
  return currentrtk_State;
}
enum Rtk_State_Status {
  Rtk_Disconnected_Unsucces,
  Rtk_Connected_Succes, // GPS detected
};
//  extern enum Obs_State obsState;
inline Rtk_State_Status& rtk_State_Status() {
  static Rtk_State_Status currentrtk_State_Status;
  return currentrtk_State_Status;
}

inline bool Rtk_Status_Connection() {
  if ((rtk_State() == Rtk_State::Rtk_Connected && rtk_State_Status() == Rtk_State_Status::Rtk_Connected_Succes )) {
    return true;
  }
  return false;
}

enum Bluetooth_State {
  Bl_Disconnected,
  Bl_Connected, // GPS detected
  Bl_Idle,
};
//  extern enum Obs_State obsState;
inline Bluetooth_State& bluetooth_State() {
  static Bluetooth_State currentbluetooth_State;
  return currentbluetooth_State;
}

enum Interval_State {
  Interval,
  Interval_In,
  Interval_out, // GPS detected
};
//  extern enum Obs_State obsState;
inline Interval_State& interval_State() {
  static Interval_State currentinterval_State;
  return currentinterval_State;
}
enum Interval_State2 {
  Interval2,
  Interval_In2,
  Interval_out2, // GPS detected
};
//  extern enum Obs_State obsState;
inline Interval_State2& interval_State2() {
  static Interval_State2 currentinterval_State2;
  return currentinterval_State2;
}

enum RTK_Mode {
  Disable_Mode,
  Survey,
  Fixed_Mode, // GPS detected
};
//  extern enum Obs_State obsState;
inline RTK_Mode& rTK_Mode() {
  static RTK_Mode currentrTK_Mode;
  return currentrTK_Mode;
}
enum RTK_Info {
  No_Fix,
  Dead_Reckoning,
  Two_D, // GPS detected
  Three_D, // GPS detected
  GNSS, // GPS detected
  Time_Fix,
};
//  extern enum Obs_State obsState;
inline RTK_Info& rTK_Info() {
  static RTK_Info currentrTK_Info;
  return currentrTK_Info;
}







enum Rover_Mode {
  Inactive, // When both AB and Auto inactive
  Active, // When Auto in active
};
//  extern enum Obs_State obsState;
inline Rover_Mode& rover_Mode() {
  static Rover_Mode currentRover_Mode;
  return currentRover_Mode;
}
enum Rover_State {
  Diconnected, // When OBS Outside Parameter
  Connected, // When Auto in active

};
//  extern enum Obs_State obsState;
inline Rover_State& rover_State() {
  static Rover_State currentRover_State;
  return currentRover_State;
}
enum Ros_State {
  Ros_Diconnected, // When OBS Outside Parameter
  Ros_Connected, // When Auto in active
  
};
//  extern enum Obs_State obsState;
inline Ros_State& ros_State() {
  static Ros_State currentRos_State;
  return currentRos_State;
}
//&& rover_State() == Rover_State::Connected)
inline bool Comm_Establish_Button() {
  if ((rover_Mode() == Rover_Mode::Active && rover_State() == Rover_State::Connected )) {
    return true;
  }
  return false;
}
inline bool Comm_Establish() {
  if ((ros_State() == Ros_State::Ros_Connected && rover_State() == Rover_State::Connected)) {
    return true;
  }
  return false;
}
enum Moving_State {
  Stop, // When OBS Outside Parameter
  Forward, // When Auto in active
  Forward_Right,
  Forward_Left,
  Backward, // When Auto in activeFlight_NN,
  Backward_Right,
  Backward_Left,
  Right,
  Left,

};
//  extern enum Obs_State obsState;
inline Moving_State& moving_State() {
  static Moving_State currentMoving_State;
  return currentMoving_State;
}

enum Value_State {
  Disable,
  Upper, // When OBS Outside Parameter
  Lower, // When Auto in active
  Double,
};
//  extern enum Obs_State obsState;
inline Value_State& value_State() {
  static Value_State currentValue_State;
  return currentValue_State;
}

enum Gps_State {
  Disconected_Gps, // No GPS detected
  Conected_Gps, // GPS detected
};
//  extern enum Obs_State obsState;
inline Gps_State& gps_State() {
  static Gps_State currentGps_State;
  return currentGps_State;
}

enum Mpu_IMU_State {
  Disconected_imu, // No GPS detected
  Conected_imu, // GPS detected
};
//  extern enum Obs_State obsState;
inline Mpu_IMU_State& mpu_IMU_State() {
  static Mpu_IMU_State currentMpu_IMU_State;
  return currentMpu_IMU_State;
}
enum Mpu_IMU_Data {
  Invalid_Data,
  Valid_Data, // GPS detected
};
//  extern enum Obs_State obsState;
inline Mpu_IMU_Data& mpu_IMU_Data() {
  static Mpu_IMU_Data currentMpu_IMU_Data;
  return currentMpu_IMU_Data;
}

inline bool Gps_Establish() { //Gps Communication Complete
  if ((gps_State() == Gps_State::Conected_Gps)) {
    return true;
  }
  return false;
}

// enum Servo9_State {
//   Servo_Disable, // When OBS Outside Parameter
//   Servo_Enable, // When Auto in active
 
  
// };
// //  extern enum Obs_State obsState;
// inline Servo9_State& servo9_State() {
//   static Servo9_State Servo9_State;
//   return Servo9_State;
// }

// inline bool Is_OA_dd() {
//   if ((flight_Mode() == Rover_Mode::Auto_FM_Active_Pre && oA_State() == OA_State::OA_Enable)) {
//     return true;
//   }
//   return false;
// }
#endif