#include <CustomStepper.h>

//Full constructor, just the first 4 parameters are necessary, they are the pins connected to the motor,
//the others are optional, and default to the following below
//the 5th paramater is the steps sequence, where the 1st element of the array is the number of steps
//it can have a maximum of 8 steps
//the 6th parameter is the SPR (Steps Per Rotation)
//the 7th parameter is the RPM
//the 8th parameter is the rotation orientation
CustomStepper stepper(8, 9, 10, 11, (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001}, 4075.7728395, 12, CW);
boolean rotate1 = false;
boolean rotatedeg = false;
boolean crotate = false;

boolean phase1 = true;
boolean phase2 = false;
boolean phase3 = false;
boolean phase4 = false;

int waitTime = 0;

void setup()
{
  //sets the RPM
  stepper.setRPM(6);
  //sets the Steps Per Rotation, in this case it is 64 * the 283712/4455 annoying ger ratio
  //for my motor (it works with float to be able to deal with these non-integer gear ratios)
  stepper.setSPR(4075.7728395);
}

void loop()
{
  
  if ( stepper.isDone() && waitTime > 0 ) {
    delay( waitTime);
    waitTime = 0;
  }
  
  // Rotate 180 degress
  if ( stepper.isDone() && phase1 == true ) {
    stepper.setDirection(CW);
    stepper.rotateDegrees(180);
    phase1 = false;
    phase2 = true;
    waitTime = 2000;
  }
  
  if ( stepper.isDone() && phase2 == true ) {
    stepper.setDirection(CCW);
    stepper.rotateDegrees(90);
    phase2 = false;
    phase3 = true;
    waitTime = 3000;
  }
  
  if ( stepper.isDone() && phase3 == true ) {
    stepper.setDirection(CW);
    stepper.rotateDegrees(90);
    phase3 = false;
    phase4 = true;
    waitTime = 5000;
  }
  
  if ( stepper.isDone() && phase4 == true ) {
    stepper.setDirection(CCW);
    stepper.rotateDegrees(180);
    //stepper.setDirection(STOP);
    phase4 = false;
    phase1 = true;
    waitTime = 10000;
  }
  
  stepper.run();
}
