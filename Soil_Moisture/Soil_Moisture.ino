// C++ code for controlling three LEDs based on soil moisture level
int moisture = 0; // Variable to store moisture sensor reading

void setup()
{
  pinMode(A0, INPUT);     // Set A0 as input for the moisture sensor
  Serial.begin(9600);     // Start serial communication
  pinMode(9, OUTPUT);     // Set pin 9 as output for LED1
  pinMode(10, OUTPUT);    // Set pin 10 as output for LED2
  pinMode(11, OUTPUT);    // Set pin 11 as output for LED3
}

void loop()
{
  moisture = analogRead(A0); // Read moisture level from the sensor
  
  // Turn off all LEDs initially
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);

  // Determine which LED to light up based on moisture level
  if (moisture < 400) {
    digitalWrite(9, HIGH); // Low moisture - LED1 ON
  } else if (moisture < 700) {
    digitalWrite(10, HIGH); // Medium moisture - LED2 ON
  } else {
    digitalWrite(11, HIGH); // High moisture - LED3 ON
  }

  delay(100); // Small delay for stability
}
