using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor LeftFront;
extern motor RightFront;
extern motor LeftBack;
extern motor RightBack;
extern motor LeftMiddle;
extern motor RightMiddle;
extern motor_group ArmMotors;
extern digital_out GBCPiston;
extern digital_out SPCPiston;
extern digital_out RDPiston;
extern digital_in LiftStop;
extern digital_in ClampDown;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );