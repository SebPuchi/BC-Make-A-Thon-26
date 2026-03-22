// Pin Assignments
const int stepPin = 5;
const int dirPin = 6;
const int enPin = 8;
const int ms1Pin = 2;
const int ms2Pin = 3;
const int ms3Pin = 4;

int stepDelay = 800;
bool isMoving = false; // Tracks if the motor should be stepping

void setup() {
  Serial.begin(9600); // Start Serial communication

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  pinMode(ms1Pin, OUTPUT);
  pinMode(ms2Pin, OUTPUT);
  pinMode(ms3Pin, OUTPUT);
  
  digitalWrite(enPin, LOW); // Enable driver
  digitalWrite(ms1Pin, LOW); // Full step
  digitalWrite(ms2Pin, LOW);
  digitalWrite(ms3Pin, LOW);
}

void loop() {
  // Check if Python sent a command
  if (Serial.available() > 0) {
    char command = Serial.read();

    if (command == 'F') {
      digitalWrite(dirPin, LOW);
      isMoving = true;
    } 
    else if (command == 'B') {
      digitalWrite(dirPin, HIGH);
      isMoving = true;
    } 
    else if (command == 'S') {
      isMoving = false;
    }
  }

  // If we are in a moving state, take one step
  if (isMoving) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepDelay);
  }
}
