//#include <SoftwareSerial.h>


// Motor pins
const int MOTOR_A_ENA = 10; // this is right motor
const int MOTOR_A_IN1 = 9;
const int MOTOR_A_IN2 = 8;
const int MOTOR_B_IN3 = 7;
const int MOTOR_B_IN4 = 6;
const int MOTOR_B_ENB = 5; // this is left motor

// Define the pins for the TCRT5000L sensor
int sensorPin1 = A5;
int sensorPin2 = A4;
int sensorPin3 = A3;
int sensorPin4 = A2;
int sensorPin5 = A1;

// Define the threshold values for the sensors
int threshold = 700;


// Define the software serial pins
//SoftwareSerial ESPSerial(6, 7);


void setup() {
  // Set the motor pins as output
  pinMode(MOTOR_A_ENA, OUTPUT);
  pinMode(MOTOR_A_IN1, OUTPUT);
  pinMode(MOTOR_A_IN2, OUTPUT);
  pinMode(MOTOR_B_ENB, OUTPUT);
  pinMode(MOTOR_B_IN3, OUTPUT);
  pinMode(MOTOR_B_IN4, OUTPUT);

  // Set the sensor pins as input
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  pinMode(sensorPin3, INPUT);
  pinMode(sensorPin4, INPUT);
  pinMode(sensorPin5, INPUT);

  // Initialize the software serial port
  //  ESPSerial.begin(9600);

  // Wait for the software serial port to initialize
  //  delay(1000);

}
void forward(int speed) {
  analogWrite(MOTOR_A_ENA, speed);
  digitalWrite(MOTOR_A_IN1, LOW);
  digitalWrite(MOTOR_A_IN2, HIGH);
  analogWrite(MOTOR_B_ENB, speed);
  digitalWrite(MOTOR_B_IN3, LOW);
  digitalWrite(MOTOR_B_IN4, HIGH);
}
void turn(int speedA, int speedB) {
  analogWrite(MOTOR_A_ENA, speedA);
  digitalWrite(MOTOR_A_IN1, LOW);
  digitalWrite(MOTOR_A_IN2, HIGH);
  analogWrite(MOTOR_B_ENB, speedB);
  digitalWrite(MOTOR_B_IN3, LOW);
  digitalWrite(MOTOR_B_IN4, HIGH);
}


void hardturnright(int speedA, int speedB) {
  analogWrite(MOTOR_A_ENA, speedA);
  digitalWrite(MOTOR_A_IN1, HIGH);
  digitalWrite(MOTOR_A_IN2, LOW);
  analogWrite(MOTOR_B_ENB, speedB);
  digitalWrite(MOTOR_B_IN3, LOW);
  digitalWrite(MOTOR_B_IN4, HIGH);
}
void hardturnleft(int speedA, int speedB) {
  analogWrite(MOTOR_A_ENA, speedA);
  digitalWrite(MOTOR_A_IN1, LOW);
  digitalWrite(MOTOR_A_IN2, HIGH);
  analogWrite(MOTOR_B_ENB, speedB);
  digitalWrite(MOTOR_B_IN3, HIGH);
  digitalWrite(MOTOR_B_IN4, LOW);
}

void loop() {
  // Read the sensor values
  int sensorValue1 = analogRead(sensorPin1);
  int sensorValue2 = analogRead(sensorPin2);
  int sensorValue3 = analogRead(sensorPin3);
  int sensorValue4 = analogRead(sensorPin4);
  int sensorValue5 = analogRead(sensorPin5);

  // Check if the robot is on the line
  if (sensorValue1 < threshold && sensorValue2 < threshold && sensorValue3 < threshold && sensorValue4 < threshold && sensorValue5 < threshold) {
    // Stop the robot
    turn(0, 255); //turn right slightly
  } else {
    // Calculate the position of the robot on the line

    int position = 0;

    if (sensorValue3 < threshold) {
      position = 3;
    }
    if (sensorValue2 < threshold) {
      position = 2;
    }

    if (sensorValue1 < threshold) {
      position = 1;
    }
    if (sensorValue4 < threshold) {
      position = 4;
    }
    if (sensorValue5 < threshold) {
      position = 5;
    }


    // Adjust the motor speed and direction based on the position
    if (position == 1) {
      // Turn left
      hardturnleft(255, 255);

    } else if (position == 2) {
      turn(255, 0);
    } else if (position == 3) {
      // Go straight
      forward(255);
    } else if (position == 4) {
      // Turn right slightly
      turn(0, 255);
    } else if (position == 5) {

      // Turn right
      hardturnright(255, 255);


    }
  }
}