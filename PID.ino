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
int threshold = 500;

// PID constants
float Kp = 0.6;
float Ki = 0.1;
float Kd = 0.1;

// Variables for PID control
float error = 0;
float last_error = 0;
float integral = 0;
float derivative = 0;
float speed = 200;
float base_speed = 200;

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
  int sensorValue1 = digitalRead(sensorPin1);
  int sensorValue2 = digitalRead(sensorPin2);
  int sensorValue3 = digitalRead(sensorPin3);
  int sensorValue4 = digitalRead(sensorPin4);
  int sensorValue5 = digitalRead(sensorPin5);

  // Calculate the error
  error = (sensorValue1 * -4) + (sensorValue2 * -1) + (sensorValue3 * 0) + (sensorValue4 * 1) + (sensorValue5 * 4);

  // Calculate the integral and derivative
  integral = integral + error;
  derivative = error - last_error;
  last_error = error;

  // Calculate the PID output
  float output = (Kp * error) + (Ki * integral) + (Kd * derivative);

  // Adjust the base speed based on the output
  speed = base_speed - output;

  // Make sure speed is within limits
  if (speed > 255) {
    speed = 255;
  } else if (speed < 0) {
    speed = 0;
  }

  // Set the motor speeds based on the error
  if (error > 0) {
    // turn left
    hardturnleft(speed, speed / 2);
  } else if (error < 0) {
    // turn right
    hardturnright(speed / 2, speed);
  } else {
    // go straight
    forward(speed);
  }
}