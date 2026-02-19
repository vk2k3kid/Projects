#include <LiquidCrystal_I2C.h> // Include the library for I2C LCD

// Initialize the LCD with I2C address and dimensions
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change 0x27 to your detected I2C address if needed

#define echoPin 2 // Echo pin of the ultrasonic sensor connected to D2
#define trigPin 3 // Trigger pin of the ultrasonic sensor connected to D3
#define buzzerPin 7 // Buzzer pin connected to D7

long duration; // Variable to store duration of pulse from ultrasonic sensor
int distance;  // Variable to store calculated distance

void setup() {
  lcd.begin(); // Initialize the LCD
  lcd.backlight(); // Turn on the backlight of the LCD

  pinMode(trigPin, OUTPUT); // Set the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);  // Set the echoPin as an INPUT
  pinMode(buzzerPin, OUTPUT); // Set the buzzerPin as an OUTPUT

  Serial.begin(9600); // Start serial communication at 9600 baud rate
  Serial.println("Distance measurement:"); 
}

void loop() {
  // Clear the trigPin by setting it LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send a 10-microsecond pulse to trigPin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the duration of the pulse on echoPin
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance (duration in microseconds divided by two and multiplied by the speed of sound in cm/us)
  distance = duration * 0.0344 / 2;

  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Display the distance on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance is:");
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print(" cm");

  // Check distance range and control buzzer
  if (distance < 90 || distance > 300) { // Distance range threshold
    tone(buzzerPin, 400, 100); // Turn on buzzer with frequency 400Hz for 100ms
  } else {
    noTone(buzzerPin); // Turn off buzzer
  }

  delay(1000); // Wait for 1 second before the next measurement
}
