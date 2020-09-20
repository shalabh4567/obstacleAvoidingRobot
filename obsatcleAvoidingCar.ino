#include <Servo.h>

#define trigPin 12
#define echoPin 13
#define motor1Input1 8 // Inputs for the motor driver L293d
#define motor1Input2 9
#define motor2Input1 10
#define motor2Input2 11
int distanceRight;
int distanceLeft;
int distanceFront;
Servo servo;


void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motor1Input1, OUTPUT);
  pinMode(motor1Input2, OUTPUT);
  pinMode(motor2Input1, OUTPUT);
  pinMode(motor2Input2, OUTPUT);
  servo.attach(7);
  servo.write(90);
  delay(300);
  distanceFront = readDistance();
}

void loop() {
  distanceRight = 0;
  distanceLeft = 0;

  if (distanceFront <= 15)
  {
    moveStop();
    delay(100);
    moveBackward();
    delay(100);
    moveStop();
    delay(200);
    distanceRight = lookRight();
    delay(200);
    distanceLeft = lookLeft();
    delay(200);

    if (distanceRight >= distanceLeft)
    {
      turnRight();
      moveStop();
    } else {
      turnLeft();
      moveStop();
    }

  } else {
    moveForward();
  }
  distanceFront = readDistance();
}
int lookLeft() {
  servo.write(30);
  delay(300);
  int distance = readDistance();
  delay(100);
  servo.write(90);
  return distance;
}
int lookRight() {
  servo.write(150);
  delay(300);
  int distance = readDistance();
  delay(100);
  servo.write(90);
  return distance;
}

int readDistance()
{
  long duration;
  int distance_in_cm;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance_in_cm = (duration / 2) / 29.1; //to get the distance in cm;
  return distance_in_cm;
}

void moveBackward() {
  digitalWrite(motor1Input1, LOW);
  digitalWrite(motor1Input2, HIGH);
  digitalWrite(motor2Input1, LOW);
  digitalWrite(motor2Input2, HIGH);
}
void turnRight() {
  digitalWrite(motor1Input1, LOW);
  digitalWrite(motor1Input2, HIGH);
  digitalWrite(motor2Input1, HIGH);
  digitalWrite(motor2Input2, LOW);
  delay(500);
  moveForward();
}
void turnLeft() {
  digitalWrite(motor1Input1, HIGH);
  digitalWrite(motor1Input2, LOW);
  digitalWrite(motor2Input1, LOW);
  digitalWrite(motor2Input2, HIGH);
  delay(500);
  moveForward();
}
void moveForward() {
  digitalWrite(motor1Input1, HIGH);
  digitalWrite(motor1Input2, LOW);
  digitalWrite(motor2Input1, HIGH);
  digitalWrite(motor2Input2, LOW);
}
void moveStop() {
  digitalWrite(motor1Input1, HIGH);
  digitalWrite(motor1Input2, HIGH);
  digitalWrite(motor2Input1, HIGH);
  digitalWrite(motor2Input2, HIGH);
}
