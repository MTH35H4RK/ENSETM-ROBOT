// Define the pins for the TCRT5000L sensor
int sensorPin1 = A5;
int sensorPin2 = A4;
int sensorPin3 = A3;
int sensorPin4 = A2;
int sensorPin5 = A1;


void setup() {
  // Set the sensor pins as input
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  pinMode(sensorPin3, INPUT);
  pinMode(sensorPin4, INPUT);
  pinMode(sensorPin5, INPUT);

  // Initialize the serial communication
  Serial.begin(9600);

}

void loop() {
  // Read the sensor values
  int sensorValue1 = analogRead(sensorPin1);
  int sensorValue2 = analogRead(sensorPin2);
  int sensorValue3 = analogRead(sensorPin3);
  int sensorValue4 = analogRead(sensorPin4);
  int sensorValue5 = analogRead(sensorPin5);


  // Print the sensor values to the serial monitor
  Serial.print("Sensor 1: ");
  Serial.print(sensorValue1);
  Serial.print(", Sensor 2: ");
  Serial.print(sensorValue2);
  Serial.print(", Sensor 3: ");
  Serial.print(sensorValue3);
  Serial.print(", Sensor 4: ");
  Serial.print(sensorValue4);
  Serial.print(", Sensor 5: ");
  Serial.println(sensorValue5);

}