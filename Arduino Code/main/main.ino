#include <AccelStepper.h>

// Define the motor interface type (8-step mode)
#define MotorInterfaceType 8

// Initialize with the sequence 1-3-2-4 for the ULN2003 driver
// Using your pins: 5, 3, 4, 2
AccelStepper stepper(MotorInterfaceType, 5, 3, 4, 2);

void setup() {
  // Max speed for these motors is usually around 500-1000 
  // steps per second with acceleration.
  stepper.setMaxSpeed(1000.0);
  stepper.setAcceleration(500.0);
  
  // Set a target position (e.g., 2 revolutions)
  stepper.moveTo(4096); 
}

void loop() {
  // If the motor reaches the target, tell it to go back
  if (stepper.distanceToGo() == 0) {
    stepper.moveTo(-stepper.currentPosition());
  }

  // This MUST be called as often as possible to keep the motor moving
  stepper.run();
}