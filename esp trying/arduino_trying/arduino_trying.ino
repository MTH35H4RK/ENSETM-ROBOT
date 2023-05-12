#include <SoftwareSerial.h>
SoftwareSerial espSerial(12, 13); // RX, TX

void setup() {
  // initialize serial:
  Serial.begin(115200);
  while (!Serial);

  espSerial.begin(9600);        // initialize ESP serial
  delay(1000);                    // Wait for the ESP to start

  Serial.println("");
  Serial.println("Arduino started");

}
String getResponse() {
  String response = "";
  while (Serial.available() > 0) {
    response += char(Serial.read());
  }
  response.trim();
  return response;
}
void loop() {
  String response = getResponse();
  Serial.println("Response: " + response);
  delay(5000);
}
