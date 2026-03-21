  #include <Stepper.h>

// The 28BYJ-48 has 2048 steps per full internal revolution
const int stepsPerRevolution = 2048;

// Initialize the stepper library on pins 5, 3, 4, 2:
// We swap pins 3 and 4 because of the 28BYJ-48's internal wiring pattern
Stepper myStepper(stepsPerRevolution, 5, 3, 4, 2);

void setup() {
  // Set the speed to 10-15 RPM (these motors are slow but high torque)
  myStepper.setSpeed(10);
  
  // Initialize serial for debugging
  Serial.begin(9600);
}

void loop() {
  // Step one revolution in one direction:
  Serial.println("Clockwise");
  myStepper.step(stepsPerRevolution);
  delay(500);

  // Step one revolution in the other direction:
  Serial.println("Counter-clockwise");
  myStepper.step(-stepsPerRevolution);
  delay(500);
}