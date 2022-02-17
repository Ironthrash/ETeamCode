/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:      8   main.cpp                                                  */
/*    Author:       C:\Users\Tiger Tech                                       */
/*    Created:      Wed Feb 09 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftFront            motor         13              
// RightFront           motor         4               
// LeftBack             motor         14              
// RightBack            motor         5               
// LeftMiddle           motor         8               
// RightMiddle          motor         9               
// ArmMotors            motor_group   10, 20          
// GBCPiston            digital_out   H               
// SPCPiston            digital_out   G               
// RDPiston             digital_out   F               
// LiftStop             digital_in    E               
// ClampDown            digital_in    C               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

#define Xpos Brain.Screen.xPosition()
#define Ypos Brain.Screen.yPosition()

using namespace vex;
// A global instance of competition
competition Competition;
// define your global instances of motors and other devices here
bool GBCPistonToggle = false;
bool SPCPistonToggle = false;
bool RDPistonToggle = false;
bool flipDirection = false;

void GBCToggle() {
  GBCPistonToggle = !GBCPistonToggle;
}

void stop() {
  LeftBack.stop();
  LeftMiddle.stop();
  LeftFront.stop();
  RightBack.stop();
  RightMiddle.stop();
  RightFront.stop();
}

void flip() {
  flipDirection = !flipDirection;
}

void SPCToggle() {
  SPCPistonToggle = !SPCPistonToggle;
}

void RDToggle() {
  RDPistonToggle = !RDPistonToggle;
}

void setSPC() {
  SPCPistonToggle = true;
}

void setRD() {
  RDPistonToggle = true;
}

const float CIRCUMFERENCE = 3.25 * 24 / 12 * M_PI;

void drive(vex::directionType direction, double velocity, vex::velocityUnits velocityUnits, double distance) {
  LeftBack.setVelocity(velocity, velocityUnits);
  LeftFront.spin(direction, velocity, velocityUnits);
  LeftMiddle.spin(direction, velocity, velocityUnits);
  RightBack.spin(direction, velocity, velocityUnits);
  RightFront.spin(direction, velocity, velocityUnits);
  RightMiddle.spin(direction, velocity, velocityUnits);
  LeftBack.spinFor(direction, distance / CIRCUMFERENCE, turns);
  stop();
  Controller1.Screen.print("done");
}

int Autonmode = 2;

void touch() {
  if (Brain.Screen.xPosition() <= 240) {
    Autonmode = 1;
  } else if (Brain.Screen.xPosition() >= 240) {
    Autonmode = 0;
  }
}
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/
void pre_auton(void) {
  Controller1.ButtonX.pressed(GBCToggle);
  Controller1.ButtonA.pressed(SPCToggle);
  Controller1.ButtonB.pressed(RDToggle);
  Controller1.ButtonUp.pressed(flip);
  ArmMotors.setStopping(brake);

  //Look at me I'm a comment

  ClampDown.low(setSPC);
  //detects when the Stationary Pneumatic Clamp limit switch is released and calls back to "setSPC"

  LiftStop.low(setRD);
  //1-31-22 detects when the lift stop limit switch is pressed and calls back to "setRDhigh"

  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(0, 0, 240, 240);
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(240, 0, 480, 240);

  Brain.Screen.pressed(touch);
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...

}
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*--------------------------------nice---------------------------------------*/

void autonomous(void) {
  Controller1.Screen.print(Autonmode);
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

  LeftFront.resetPosition();
  LeftMiddle.resetPosition();
  LeftBack.resetPosition();
  RightFront.resetPosition();
  RightMiddle.resetPosition();
  RightBack.resetPosition();

  if (Autonmode == 0) {

    GBCPiston.set(false);
    SPCPiston.set(true);
    RDPiston.set(true);

    drive(forward, 100, vex::velocityUnits::pct, 38);
    //

    LeftFront.setStopping(brake);
    LeftMiddle.setStopping(brake);
    LeftBack.setStopping(brake);
    RightFront.setStopping(brake);
    RightMiddle.setStopping(brake);
    RightBack.setStopping(brake);
    wait(0.3, seconds);
    LeftFront.setStopping(coast);
    LeftMiddle.setStopping(coast);
    LeftBack.setStopping(coast);
    RightFront.setStopping(coast);
    RightMiddle.setStopping(coast);
    RightBack.setStopping(coast);

    drive(forward, 50, vex::velocityUnits::pct, 6);

    //RDPiston.set(true);
    //the ratchet drive disengages for more precise turning

    //drive(forward,75,vex::velocityUnits::pct,96);
    //stop();
    //the robot drives forward 96 inches

    //wait(0.3, seconds);
    //buffer

    //RightBack.setVelocity(25, pct);
    //LeftFront.spin(reverse,25,velocityUnits::pct);
    //LeftBack.spin(reverse,25,velocityUnits::pct);
    //LeftMiddle.spin(reverse,25,velocityUnits::pct);
    //RightFront.spin(forward,25,velocityUnits::pct);
    //RightMiddle.spin(forward,25,velocityUnits::pct);
    //RightBack.spinFor(forward,26.66/CIRCUMFERENCE,turns);
    //RightFront.stop();
    //RightMiddle.stop();
    //RightBack.stop();
    //LeftFront.stop();
    //LeftBack.stop();
    //LeftMiddle.stop();
    //the robot spins for around 180 degrees counterclockwise

    //LeftBack.setVelocity(50, pct);
    //LeftFront.spin(reverse,50,velocityUnits::pct);
    //LeftMiddle.spin(reverse,50,velocityUnits::pct);
    //LeftBack.spinFor(reverse,7/CIRCUMFERENCE,turns);
    //LeftFront.stop();
    //LeftMiddle.stop();
    //LeftBack.stop();
    //robot does a roughly 45 degree arc turn clockwise

    //wait(0.3, seconds);
    //buffer

    //drive(forward, 75, vex::velocityUnits::pct, 24); //return distance back to 102 later
    //stop();
    //the robot drives forward for 102 inches (derived from the fact that I wanted to have the robot drive accross 3 diagonal tiles: 3 * square root of 2 * 24)

    //wait(0.1, seconds);
    //buffer

    //LeftBack.setVelocity(50, pct);
    //LeftFront.spin(forward,50,velocityUnits::pct);
    //LeftMiddle.spin(forward,50,velocityUnits::pct);
    //LeftBack.spinFor(forward,7/CIRCUMFERENCE,turns);
    //LeftFront.stop();
    //LeftMiddle.stop();
    //LeftBack.stop();
    //robot does a roughly 45 degree arc turn clockwise

    //wait(0.1, seconds);
    //buffer

    //drive(forward,75,vex::velocityUnits::pct,96);
    //stop();
    //the robot drives forward 96 inches

  } else if (Autonmode == 1) {
    GBCPiston.set(false);
    SPCPiston.set(true);
    RDPiston.set(true);

    //front claw opens, back clamp closes, Ratchet Drive disengages

    drive(forward, 100, vex::velocityUnits::pct, 38);
    //the robot drives forward 44 inches at 75 pct speed
    //1/28/22 changed speed to 80 pct, then 100 pct, & distance to 38 inches

    LeftFront.setStopping(brake);
    LeftMiddle.setStopping(brake);
    LeftBack.setStopping(brake);
    RightFront.setStopping(brake);
    RightMiddle.setStopping(brake);
    RightBack.setStopping(brake);
    wait(0.3, seconds);
    LeftFront.setStopping(coast);
    LeftMiddle.setStopping(coast);
    LeftBack.setStopping(coast);
    RightFront.setStopping(coast);
    RightMiddle.setStopping(coast);
    RightBack.setStopping(coast);
    //the motors then brake for 0.2 seconds so that the resistance on each motor is equalized
    //1/28/22 changed braking time to 0.3 seconds

    drive(forward, 50, vex::velocityUnits::pct, 6);
    //the robot drives forward 4 inches at 50 pct speed
    //1/28/22 increased distance traveled to 6 inches

    GBCPiston.set(true);
    SPCPiston.set(false);
    //the clamper closes and the pneumatic clamp opens

    wait(0.1, seconds);
    //the robot waits for 0.1 seconds

    ArmMotors.spin(reverse, 100, pct);
    wait(0.5, seconds);
    ArmMotors.stop();
    //the 4 bar lift lifts up at full speed for 0.5 seconds

    drive(reverse, 50, vex::velocityUnits::pct, 40);
    //the robot drives backward for 54 inches

    RightBack.setVelocity(50, pct);
    RightFront.spin(forward, 50, velocityUnits::pct);
    RightMiddle.spin(forward, 50, velocityUnits::pct);
    RightBack.spinFor(forward, 15 / CIRCUMFERENCE, turns);
    RightFront.stop();
    RightMiddle.stop();
    RightBack.stop();
    //the robot should turn roughly 90 degrees counterclockwise

    RightMiddle.spin(reverse, 50, pct);
    RightBack.spin(reverse, 50, pct);
    RightFront.spin(reverse, 50, pct);
    LeftFront.spin(reverse, 50, pct);
    LeftBack.spin(reverse, 50, pct);
    LeftMiddle.spin(reverse, 50, pct);
    wait(1, seconds);
    stop();
    //the robot drives backwards for 24 inches based off the velocity of our robot
    //(400 rpm * 1/60 * 3.25in * pi = roughly 68.0678408278 inches per seconds)
    //1-31-22 changed the time to 1 seconds because that distance wasn't right & 1 second will work

    SPCPiston.set(true);
    //the back clamp closes
    RDPiston.set(false);
    //the ratchet drive engages

    wait(1, seconds);
    //the robot waits for 1 second

    drive(forward, 50, velocityUnits::pct, 10);
    //the robot drives forward 10 inches
    RightBack.setVelocity(25, pct);
    LeftFront.spin(reverse, 25, velocityUnits::pct);
    LeftBack.spin(reverse, 25, velocityUnits::pct);
    LeftMiddle.spin(reverse, 25, velocityUnits::pct);
    RightFront.spin(forward, 25, velocityUnits::pct);
    RightMiddle.spin(forward, 25, velocityUnits::pct);
    RightBack.spinFor(forward, (40 / CIRCUMFERENCE), turns);
    RightFront.stop();
    RightMiddle.stop();
    RightBack.stop();
    LeftFront.stop();
    LeftBack.stop();
    LeftMiddle.stop();
    //the robot spins for around 270 degrees counterclockwise

    drive(reverse, 100, vex::velocityUnits::pct, 10);
    //robot drives backward 10 inches

  } else if (Autonmode == 2) {
    GBCPiston.set(false);
    SPCPiston.set(true);
    RDPiston.set(true);
    //1-29-22 front claw opens, back clamp closes, Ratchet Drive disengages

    drive(forward, 50, vex::velocityUnits::pct, 44);
    stop();
    //1-29-22 the robot drives forward 44 inches at 80 pct speed
    //1-31-22 changed speed to 50 pct

    LeftFront.setStopping(brake);
    LeftMiddle.setStopping(brake);
    LeftBack.setStopping(brake);
    RightFront.setStopping(brake);
    RightMiddle.setStopping(brake);
    RightBack.setStopping(brake);
    wait(0.4, seconds);
    LeftFront.setStopping(coast);
    LeftMiddle.setStopping(coast);
    LeftBack.setStopping(coast);
    RightFront.setStopping(coast);
    RightMiddle.setStopping(coast);
    RightBack.setStopping(coast);
    //1-29-22 the motors then brake for 0.4 seconds so that the resistance on each motor is equalized

    drive(forward, 50, vex::velocityUnits::pct, 6);
    stop();
    //1-29-22 the robot drives forward 6 inches at 50 pct speed
    GBCPiston.set(true);
    //1-29-22 Goal Base Clamper Piston activates

    wait(0.1, seconds);
    //1-29-22 the robot waits for 0.1 seconds

    ArmMotors.spin(reverse, 100, pct);
    wait(0.5, seconds);
    ArmMotors.stop();
    //1-29-22 the 4 bar lift lifts up at full speed for 0.5 seconds

    wait(1, seconds);
    //1-29-22 the robot waits for 1 seconds

    drive(forward, 50, vex::velocityUnits::pct, 10);
    stop();
    //1-29-22 the robot drives forward 10 inches at 50 pct speed

    wait(1, seconds);
    //1-29-22 the robot waits for 1 seconds

    RightBack.setVelocity(25, pct);
    LeftFront.spin(reverse, 25, velocityUnits::pct);
    LeftBack.spin(reverse, 25, velocityUnits::pct);
    LeftMiddle.spin(reverse, 25, velocityUnits::pct);
    RightFront.spin(forward, 25, velocityUnits::pct);
    RightMiddle.spin(forward, 25, velocityUnits::pct);
    RightBack.spinFor(forward, (7 / CIRCUMFERENCE), turns);
    RightFront.stop();
    RightMiddle.stop();
    RightBack.stop();
    LeftFront.stop();
    LeftBack.stop();
    LeftMiddle.stop();
    //1-29-22 the robot spins for around 45 degrees counterclockwise
    //1-31-22 changed distance from 6.667 to 6.25 then 7 cause that was the wrong direction, then back to 6 becuase I was wrong about that being the wrong direction
    //2-8-22 changed distance to 5.5 in. because a shallower turn was needed
    //2-11-22 changed distance to 6 in. because a test showed that a wider turn was needed
    //2-17-22 changed distance to 7 in. because a test showed that a wider turn was needed

    wait(1, seconds);
    //1-29-22 the robot waits for 1 seconds

    ArmMotors.spin(reverse, 100, pct);
    wait(1, seconds);
    ArmMotors.stop();
    //1-29-22 the 4 bar lift lifts up at full speed for 2 seconds
    //1-31-22 changed time to 1.5 then 1

    wait(1, seconds);
    //1-29-22 the robot waits for 1 seconds

    drive(forward, 50, vex::velocityUnits::pct, 34);
    stop();
    //1-29-22 the robot drives forward 68 inches at 50 pct speed
    //RightMiddle.spin(forward, 50, pct);
    //RightBack.spin(forward, 50, pct);
    //RightFront.spin(forward, 50, pct);
    //LeftFront.spin(forward, 50, pct);
    //LeftBack.spin(forward, 50, pct);
    //LeftMiddle.spin(forward, 50, pct);
    //wait(1.3, seconds);
    //stop();
    //1-31-22 the robot drives forward for 68 inches based off the velocity of our robot
    //1-31-22(400 rpm * 1/60 * 3.25in * pi = roughly 68.0678408278 inches per second)
    //1-31-22 0.2 seconds was added because 1 didn't go far enough
    //1-31-22 time changed to 1.3 b/c 0.2 was too much
    //2-11-22 segment changed to be distance based instead of time based because nothing should be in the way
    //2-11-22 distance was changed to 60 in. b/c 68 was too far
    //2-11-22 distance was changed to 44 in. b/c 60 was way too far
    //2-11-22 distance was changed to 34 in. b/c 44 was way too far

    wait(1, seconds);
    //1-29-22 the robot waits for 1 seconds

    RightBack.setVelocity(25, pct);
    LeftFront.spin(forward, 25, velocityUnits::pct);
    LeftBack.spin(forward, 25, velocityUnits::pct);
    LeftMiddle.spin(forward, 25, velocityUnits::pct);
    RightFront.spin(reverse, 25, velocityUnits::pct);
    RightMiddle.spin(reverse, 25, velocityUnits::pct);
    RightBack.spinFor(reverse, (7 / CIRCUMFERENCE), turns);
    RightFront.stop();
    RightMiddle.stop();
    RightBack.stop();
    LeftFront.stop();
    LeftBack.stop();
    LeftMiddle.stop();
    //1-31-22 the robot spins for around 45 degrees counterclockwise
    //2-8-22 changed distance to 5.5 inches to match previous turn
    //2-11-22 changed distance to 6 inches to match previous turn
    //2-17-22 changed distance to 7 inches to match previous turn

    wait(1, seconds);
    //1-31-22 buffer for testing

    drive(forward, 50, vex::velocityUnits::pct, 8);
    stop();
    //1-31-22 the robot drive 4 inches forward at 50 pct speed
    //2-17-22 distance changed to 8 inches b/c 4 was not enough

    ArmMotors.spin(forward, 100, pct);
    wait(0.5, seconds);
    ArmMotors.stop();
    //1-29-22 the 4 bar lowers up at full speed for 1 seconds
    //1-31-22 changed time to 0.5 seconds

    wait(1, seconds);
    //1-29-22 the robot waits for 1 seconds

    GBCPiston.set(false);
    //1-29-22 the Goal Base Clamper Piston deactivates

    wait(1, seconds);
    //1-29-22 the robot waits for 1 seconds

    drive(reverse, 50, vex::velocityUnits::pct, 2);
    stop();
    //1-29-22 the robot drives backward 2 inches at 50 pct speed

    wait(1, seconds);
    //1-29-22 the robot waits for 1 seconds

    ArmMotors.spin(reverse, 100, pct);
    wait(0.5, seconds);
    ArmMotors.stop();
    //1-29-22 the 4 bar lift lifts up at full speed for 1 seconds
    //1-31-22 changed time to 0.5 seconds

    wait(1, seconds);
    //1-29-22 the robot waits for 1 seconds

    drive(reverse, 50, vex::velocityUnits::pct, 80);
    stop();
    //1-29-22 the robot drives backward 10 inches at 50 pct speed
    //2-17-22 temporarily changed distance to 80 to score tall neutral Mobile Goal
  }
}
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.
    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    LeftFront.spin(forward, Controller1.Axis3.value() + Controller1.Axis1.value() / 2, pct);
    LeftMiddle.spin(forward, Controller1.Axis3.value() + Controller1.Axis1.value() / 2, pct);
    LeftBack.spin(forward, Controller1.Axis3.value() + Controller1.Axis1.value() / 2, pct);
    RightFront.spin(forward, Controller1.Axis3.value() - Controller1.Axis1.value() / 2, pct);
    RightMiddle.spin(forward, Controller1.Axis3.value() - Controller1.Axis1.value() / 2, pct);
    RightBack.spin(forward, Controller1.Axis3.value() - Controller1.Axis1.value() / 2, pct);

    if (Controller1.ButtonL1.pressing()) {
      ArmMotors.spin(reverse, 100, pct);
    } else if (Controller1.ButtonL2.pressing() && LiftStop.value() == 1) {
      ArmMotors.spin(forward, 100, pct);
    } else {
      ArmMotors.stop();
    }

    if (GBCPistonToggle) {
      GBCPiston.set(true);
    } else {
      GBCPiston.set(false);
    }

    if (SPCPistonToggle) {
      SPCPiston.set(true);
    } else {
      SPCPiston.set(false);
    }

    if (RDPistonToggle) {
      RDPiston.set(true);
    } else {
      RDPiston.set(false);
    }

    wait(20, msec); // Sleep the task for a short amount of time to
    // prevent wasted resources.
  }
}
//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  // Run the pre-autonomous function.
  pre_auton();
  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}