const int soundSensorPin = A0; // Sound sensor connected to analog pin A0
const int ledPin = 2;          // LED connected to digital pin D2

int sensorValue = 0;           // Store the sensor value
int threshold = 600;           // Threshold for loud noise (clap)
unsigned long previousMillis = 0;
const long interval = 500;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);          // For debugging
}

void loop() {
  sensorValue = analogRead(soundSensorPin);

  // Monitor sensor values
  Serial.println(sensorValue);

  // Trigger LED if sensor value exceeds threshold
  if (sensorValue > threshold) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      digitalWrite(ledPin, HIGH);
      delay(200); // LED on for 200ms
      digitalWrite(ledPin, LOW);
    }
  }

  delay(10); // Small delay to prevent overwhelming the processor
}
