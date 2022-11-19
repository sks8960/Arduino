#include <Servo.h>
Servo servoLeft;
Servo servoRight;
byte wLeftOld;
byte wRightOld;

void setup() {
  pinMode(7, INPUT);
  pinMode(5, INPUT);
  pinMode(8, OUTPUT);
  pinMode(2, OUTPUT);
  tone(4, 3000, 1000);
  delay(1000);
  servoLeft.attach(13);
  servoRight.attach(12);
  wLeftOld = 0;
  wRightOld = 1;
}

void loop() {
  byte wLeft = digitalRead(5);
  byte wRight = digitalRead(7);
  if((wLeft == 0) && (wRight == 0))
  {
    backward(1000);
    turnRight(400);
  }
  else if(wLeft == 0)
  {
    int Rspeed = 1400;
    bigCircle(1000, Rspeed);
  }
  else if(wRight == 0)
  {
    int Rspeed = 1400;
    smallCircle(1000, Rspeed);
  }
  else
  {
    int Rspeed = 1400;
    Circle(20, Rspeed);
  }

}
void bigCircle(int time, int Rspeed)
{
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(Rspeed);
  Rspeed = Rspeed -20;
}

void smallCircle(int time, int Rspeed)
{
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(Rspeed);
  Rspeed = Rspeed + 20;
}

void Circle(int time, int Rspeed)
{
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(Rspeed);
}

void forward(int time)
{
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
  delay(time);
}
void turnLeft(int time)
{
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1300);
  delay(time);
}
void turnRight(int time)
{
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1700);
  delay(time);
}
void backward(int time)
{
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1700);
  delay(time);
}
