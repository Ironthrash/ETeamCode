#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LeftFront = motor(PORT13, ratio18_1, false);
motor RightFront = motor(PORT4, ratio18_1, true);
motor LeftBack = motor(PORT14, ratio18_1, false);
motor RightBack = motor(PORT5, ratio18_1, true);
motor LeftMiddle = motor(PORT8, ratio18_1, true);
motor RightMiddle = motor(PORT9, ratio18_1, false);
motor ArmMotorsMotorA = motor(PORT10, ratio18_1, false);
motor ArmMotorsMotorB = motor(PORT20, ratio18_1, true);
motor_group ArmMotors = motor_group(ArmMotorsMotorA, ArmMotorsMotorB);
digital_out GBCPiston = digital_out(Brain.ThreeWirePort.H);
digital_out SPCPiston = digital_out(Brain.ThreeWirePort.G);
digital_out RDPiston = digital_out(Brain.ThreeWirePort.F);
digital_in LiftStop = digital_in(Brain.ThreeWirePort.E);
digital_in ClampDown = digital_in(Brain.ThreeWirePort.C);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}