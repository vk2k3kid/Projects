// Define pin numbers
const int redPin = 11;    // Red LED pin
const int greenPin = 10; // Green LED pin
const int bluePin = 9;  // Blue LED pin
const int buzzerPin = 8; // Buzzer pin

// Define buzzer frequencies for musical notes (in Hz)
const int saFrequency = 262;  // C (Sa)
const int reFrequency = 294;  // D (Re)
const int gaFrequency = 330;  // E (Ga)
const int maFrequency = 349;  // F (Ma)
const int paFrequency = 392;  // G (Pa)

// Function to set color and play sound
void setColor(int redValue, int greenValue, int blueValue, int frequency) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
  tone(buzzerPin, frequency);
}

void setup() {
  // Set LED and Buzzer pins as outputs
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Red (Sa)
  setColor(255, 0, 0, saFrequency);
  delay(2000);

  // Green (Re)
  setColor(0, 255, 0, reFrequency);
  delay(2000);

  // Blue (Ga)
  setColor(0, 0, 255, gaFrequency);
  delay(2000);

  // Yellow (Red + Green) (Ma)
  setColor(255, 255, 0, maFrequency);
  delay(2000);

  // Cyan (Green + Blue) (Pa)
  setColor(0, 255, 255, paFrequency);
  delay(2000);

  // Magenta (Red + Blue) (Sa)
  setColor(255, 0, 255, saFrequency);
  delay(2000);

  // White (Red + Green + Blue) (Re)
  setColor(255, 255, 255, reFrequency);
  delay(2000);

  // Turn off all LEDs and stop sound
  setColor(0, 0, 0, 0);
  noTone(buzzerPin);  // Stop any sound playing
  delay(1000);        // Wait for 1 second before repeating
}
