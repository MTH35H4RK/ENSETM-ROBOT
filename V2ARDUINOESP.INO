#include <SoftwareSerial.h>

SoftwareSerial espSerial(12, 13); // RX, TX

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

String sendGETRequest(String url) {
  String response = "";
  if (espSerial.available()) {
    while (espSerial.available()) {
      espSerial.read();
    }
  }
  espSerial.println(url);
  delay(1000);
  if (espSerial.available()) {
    response = espSerial.readStringUntil('\n');
  }
  return response;
}

String getAccident() {
  String url = "/ACCIDENT/XXXXX";
  return sendGETRequest(url);
}

String getHospital() {
  String url = "/HOSPITAL/XXXXX";
  return sendGETRequest(url);
}

String getTraffic() {
  String url = "/TRAFFIC/XXXXX";
  return sendGETRequest(url);
}

String changeTrafficLight() {
  String response = "";
  String url = "/LIGHT/XXXXX";
  String status = sendGETRequest(url);
  if (status == "RED") {
    String greenUrl = "/GREEN/XXXXX";
    String greenResponse = sendGETRequest(greenUrl);
    if (greenResponse == "CHANGED") {
      response = "GREEN";
    } else {
      response = "Traffic light change failed";
    }
  }
  else if (status == "GREEN") {
    response = "GREEN";
  }

  return response;
}

void loop() {
  String accidentResponse = getAccident();
  if (accidentResponse != "") {
    Serial.println("Received accident: " + accidentResponse);
    // Do something with the response variable
  }

  String hospitalResponse = getHospital();
  if (hospitalResponse != "") {
    Serial.println("Received hospital: " + hospitalResponse);
    // Do something with the response variable
  }

  String trafficResponse = getTraffic();
  if (trafficResponse != "") {
    Serial.println("Received traffic: " + trafficResponse);
    // Do something with the response variable
  }

  String lightResponse = changeTrafficLight();
  if (lightResponse != "") {
    Serial.println(lightResponse);
  }

  delay(5000);
}