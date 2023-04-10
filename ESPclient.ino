
#include <WiFi.h>
#include <HTTPClient.h>
#include <SoftwareSerial.h>


SoftwareSerial mySerial(10, 11); // RX, TX


// Replace with your network credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Replace with your server IP address and port number
const char* server_ip = "192.168.X.X";
const int server_port = 5000;

// Replace with your authorization code
const char* authorization_code = "XXXXX";

// Endpoint URLs
const String check_url = "/CHECK/" + String(authorization_code);
const String accident_url = "/ACCIDENT/" + String(authorization_code);
const String hospital_url = "/HOSPITAL/" + String(authorization_code);
const String light_url = "/LIGHT/" + String(authorization_code);
const String green_url = "/GREEN/" + String(authorization_code);
const String traffic_url = "/TRAFFIC/" + String(authorization_code);

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  // Check server connection and authorization code
  if (checkConnection()) {
    // Get accident position
    String accident_pos = getPosition(accident_url);
    Serial.println("Accident position: " + accident_pos);

    // Stop for 5 seconds at accident position
    stopAtPosition(accident_pos, 5000);

    // Cross the roundabout
    crossRoundabout();

    // Get hospital ID
    String hospital_id = getHospital(hospital_url);
    Serial.println("Hospital ID: " + hospital_id);

    // Check traffic and take available path
    String traffic_pos = getPosition(traffic_url);
    Serial.println("Traffic position: " + traffic_pos);
    if (traffic_pos == "V11" || traffic_pos == "V21") {
      takePath("P12");
    } else {
      takePath("P22");
    }

    // Check traffic light state and act accordingly
    String light_state = getLightState(light_url);
    Serial.println("Light state: " + light_state);
    if (light_state == "RED") {
      changeLightState();
    } else {
      // Pass automatically
      Serial.println("Passing automatically");
    }
  }

  delay(5000); // Wait 5 seconds before sending the next request
}

bool checkConnection() {
  HTTPClient http;
  http.begin("http://" + String(server_ip) + ":" + String(server_port) + check_url);

  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK) {
    String response = http.getString();
    Serial.println("Server response: " + response);
    if (response == "SUCCESS") {
      return true;
    }
  }

  Serial.println("Failed to check server connection");
  return false;
}

String getPosition(String url) {
  HTTPClient http;
  http.begin("http://" + String(server_ip) + ":" + String(server_port) + url);

  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK) {
    String response = http.getString();
    Serial.println("Server response: " + response);
    if (response != "FAILED") {
      return response;
    }
  }

  Serial.println("Failed to get position");
  return "";
}

void stopAtPosition(String position, int duration) {
  Serial.println("Stopping at position " + position);
  delay(duration);
}

void crossRoundabout() {
  Serial.println("Crossing roundabout");
// Code for crossing the roundabout
}

String getHospital(String url) {
HTTPClient http;
http.begin("http://" + String(server_ip) + ":" + String(server_port) + url);

int httpCode = http.GET();
if (httpCode == HTTP_CODE_OK) {
String response = http.getString();
Serial.println("Server response: " + response);
if (response != "FAILED") {
return response;
}
}

Serial.println("Failed to get hospital ID");
return "";
}

void takePath(String path) {
Serial.println("Taking path " + path);
// Code for taking the path
}

String getLightState(String url) {
HTTPClient http;
http.begin("http://" + String(server_ip) + ":" + String(server_port) + url);

int httpCode = http.GET();
if (httpCode == HTTP_CODE_OK) {
String response = http.getString();
Serial.println("Server response: " + response);
if (response != "FAILED") {
return response;
}
}

Serial.println("Failed to get light state");
return "";
}

void changeLightState() {
Serial.println("Changing light state");
// Code for changing the traffic light state
}