int buzzerPin = 8;
int sirenState = 0;
unsigned long lastSirenChangeTime = 0;

void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Change siren state every 400 milliseconds
  if (currentMillis - lastSirenChangeTime >= 400) {
    lastSirenChangeTime = currentMillis;
    sirenState = 1 - sirenState;
    
    // Play tone based on siren state
    if (sirenState == 1) {
      tone(buzzerPin, 880);
    } else {
      tone(buzzerPin, 660);
    }
  }
  
  //CODE GLOBAL AYKON HNA
}
