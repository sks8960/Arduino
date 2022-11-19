#include <SoftwareSerial.h>
#include <Servo.h>
Servo servoLeft;             // Declare left and right servos
Servo servoRight;
Servo servo;
int bluetoothTx = 7;
int bluetoothRx = 6;

SoftwareSerial BT(bluetoothTx, bluetoothRx);

// 아두이노 초기화
void setup() 
{
    Serial.begin(9600);
    BT.begin(9600);
    Serial.println("Bluetooth Module Setup Mode");
    pinMode(10, INPUT); pinMode(9, OUTPUT);  //Left IR LED & Receiver
    pinMode(3, INPUT);  pinMode(2, OUTPUT);   // Right IR LED & Receiver
    tone(4, 3000, 1000);        // Play tone for 1 second
    delay(1000);              // Delay to finish tone
}
void loop() 
{
  char cmd;
  if (BT.available()) {     //블루투스가 연결되어 사용 가능하다면
    cmd = (char)BT.read();
    Serial.print("Command = ");
    Serial.println(cmd);
    
    if(cmd == '1')
    {
      Serial.println("Power ON");
      servoLeft.attach(13);      // Attach left signal to pin 13
      servoRight.attach(12);      // Attach right signal to pin 12
      servo.attach(11);
    }
  
    if(cmd == '2')
    {
      Serial.println("Power OFF");
      servoLeft.detach();
      servoRight.detach();
      servo.detach();
    }
  }
    myServo();
  int irLeft = irDetect(9, 10, 55000); // Check for object on left
  int irRight = irDetect(2, 3, 55000);// Check for object on right
 if((irLeft == 0) && (irRight == 0)) // If both sides detect
  {maneuver(-50, -50, 20);  }    // Backward 20 milliseconds
  else if(irLeft == 0)          // If only left side detects
  {maneuver(50, -50, 20);    }    // Right for 20 ms
  else if(irRight == 0)        // If only right side detects
  {maneuver(-50, 50, 20);    }     // Left for 20 ms
  else                          // Otherwise, no IR detects
  {maneuver(50, 50, 20);      }    // Forward 20 ms
}
int irDetect(int irLedPin, int irReceiverPin, long frequency)
{ tone(irLedPin, frequency, 8);  // IRLED 38 kHz for at least 1 ms
  delay(1);                       // Wait 1 ms
  int ir = digitalRead(irReceiverPin);// IR receiver -> ir variable
  delay(1);                   // Down time before recheck
  return ir;               }      // Return 1 no detect, 0 detect


void maneuver(int speedLeft, int speedRight, int msTime)
{ // speedLeft, speedRight ranges: Backward  Linear  
  // Stop  Linear   Forward
  //     -200      -100......0......100       200
  // Set Left servo speed
  servoLeft.writeMicroseconds(1500 + speedLeft);
  // Set right servo speed
  servoRight.writeMicroseconds(1500 - speedRight);
  if(msTime==-1)               // if msTime = -1
  { servoLeft.detach();         // Stop servo signals
    servoRight.detach();   }
  delay(msTime);               // Delay for msTime
}

void myServo(){
  servo.write(180);
  delay(150);
  servo.write(40);
  delay(150);
}
