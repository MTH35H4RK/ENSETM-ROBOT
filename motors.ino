
// Motor pins
const int MOTOR_A_ENA = 10; // this is right motor
const int MOTOR_A_IN1 = 9;
const int MOTOR_A_IN2 = 8;
const int MOTOR_B_IN3 = 7;
const int MOTOR_B_IN4 = 6;
const int MOTOR_B_ENB = 5; // this is left motor

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
void setup() {

  pinMode(MOTOR_A_ENA, OUTPUT);
  pinMode(MOTOR_A_IN1, OUTPUT);
  pinMode(MOTOR_A_IN2, OUTPUT);
  pinMode(MOTOR_B_ENB, OUTPUT);
  pinMode(MOTOR_B_IN3, OUTPUT);
  pinMode(MOTOR_B_IN4, OUTPUT);
}

void loop() {
  forward(255);

  delay(1000);
  
  turn(200,0); //turn left
  
  delay(1000);
  
  turn(0,200); //turn right
  
  delay(1000);
}