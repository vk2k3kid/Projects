// Define pins for the ultrasonic sensor and the buzzer
const int trigPin = 9;
const int echoPin = 10;
const int buzzer = 11;

// Variables to store the duration and distance
long duration;
int distance;

void setup() {
  // Initialize the serial monitor
  Serial.begin(9600);

  // Set the trigPin as output and echoPin as input
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set the buzzer as output
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // Send a 10us HIGH pulse to the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the pulse on the echo pin
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in cm (sound travels at 343m/s, or 0.0343 cm/us)
  distance = duration * 0.034 / 2;

  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // If an obstacle is within 50 cm, turn on the buzzer
  if (distance <= 50 && distance > 0) {
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
  }

  // Small delay before the next reading
  delay(200);
}
