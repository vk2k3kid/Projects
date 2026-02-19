/* 
 * Obstacle Avoiding Robot Using Ultrasonic Sensor and Arduino UNO
 * Optimized Code to Ensure Proper Forward Movement After Turning
 */

// Ultrasonic Sensor Pins
int trigPin = 9;     // Trig pin of HC-SR04
int echoPin = 10;    // Echo pin of HC-SR04

// Motor Driver Pins
int ENA = 11;        // Speed control for the right motor
int ENB = 3;         // Speed control for the left motor
int revleft4 = 4;    // Reverse motion of the left motor
int fwdleft5 = 5;    // Forward motion of the left motor
int revright6 = 6;   // Reverse motion of the right motor
int fwdright7 = 7;   // Forward motion of the right motor

// Variables
long duration, distance;

void setup() {
  Serial.begin(9600);            // Initialize serial communication
  
  // Motor pins
  pinMode(ENA, OUTPUT);          // Enable pin for the right motor
  pinMode(ENB, OUTPUT);          // Enable pin for the left motor
  pinMode(revleft4, OUTPUT);     
  pinMode(fwdleft5, OUTPUT);
  pinMode(revright6, OUTPUT);
  pinMode(fwdright7, OUTPUT);

  // Ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);      // Trig pin as output
  pinMode(echoPin, INPUT);       // Echo pin as input
  
  // Set initial motor speed
  analogWrite(ENA, 200);         // Set right motor speed (range: 0-255)
  analogWrite(ENB, 200);         // Set left motor speed (range: 0-255)
}

void loop() {
  // Trigger ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Calculate distance
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;   // Convert to distance in cm
  
  Serial.print("Distance: ");
  Serial.println(distance);     // Print distance for debugging
  
  // Robot movement based on distance
  if (distance > 20) {
    // Move forward
    digitalWrite(fwdright7, HIGH);
    digitalWrite(revright6, LOW);
    digitalWrite(fwdleft5, HIGH);
    digitalWrite(revleft4, LOW);
  } 
  else if (distance <= 20 && distance > 5) {
    // Stop and avoid obstacle
    stopMotors();
    delay(500);

    // Move backward
    digitalWrite(fwdright7, LOW);
    digitalWrite(revright6, HIGH);
    digitalWrite(fwdleft5, LOW);
    digitalWrite(revleft4, HIGH);
    delay(500);

    // Stop again
    stopMotors();
    delay(500);

    // Turn right
    digitalWrite(fwdright7, LOW);
    digitalWrite(revright6, LOW);
    digitalWrite(fwdleft5, HIGH);
    digitalWrite(revleft4, LOW);
    delay(500);

    // Stop after turning
    stopMotors();
    delay(500);
  }
  else {
    // If obstacle is very close (< 5 cm), stop completely
    stopMotors();
    delay(500);
  }

  delay(100);  // Small delay for stability
}

// Function to stop all motors
void stopMotors() {
  digitalWrite(fwdright7, LOW);
  digitalWrite(revright6, LOW);
  digitalWrite(fwdleft5, LOW);
  digitalWrite(revleft4, LOW);
}
