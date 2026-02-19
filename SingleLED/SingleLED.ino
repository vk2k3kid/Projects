// Pin definitions
const int ledPin = 13;    // Pin for LED
const int buzzerPin = 8;  // Pin for Buzzer

// Define intensity levels and corresponding buzzer frequencies (in Hz)
int intensities[] = {50, 100, 150, 200, 255};  // LED brightness levels (0 to 255)
int frequencies[] = {262, 294, 330, 349, 392}; // Frequencies for C4, D4, E4, F4, G4 notes

void setup() {
  pinMode(ledPin, OUTPUT);    // Set LED pin as output
  pinMode(buzzerPin, OUTPUT); // Set Buzzer pin as output
}

void loop() {
  // Loop through each intensity level
  for (int i = 0; i < 5; i++) {
    analogWrite(ledPin, intensities[i]);  // Set LED brightness
    tone(buzzerPin, frequencies[i], 500); // Play sound for 500 milliseconds
    delay(1000);                          // Wait for 1 second
  }

  delay(2000); // Pause before repeating
}
