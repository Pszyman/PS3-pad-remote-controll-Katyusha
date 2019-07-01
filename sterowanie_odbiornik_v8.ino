#include <Servo.h>

Servo myservoSteering;
Servo myservoLR;
Servo myservoBT; 


const int RYF =  2;
const int RYB =  3;
int rocketCurrent = 7;
int fire = 0;

int LX =  128;
int LY =  128;
int RY =  128;
int RX =  128;
int mode = 1;
int sum=0;

int RXR2;
int RXL2;


void setup() {
  Serial.begin(9600);

  pinMode(RYF, OUTPUT);
  pinMode(RYB, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  
  myservoSteering.attach(4);
  myservoLR.attach(5);
  myservoBT.attach(6);

}

void loop() {

  if(Serial.available() >= 8){
 if(Serial.read()==0xC8){
      byte discard = Serial.read();
      LX =  (Serial.read());
      LY =  (Serial.read());
      RX =  (Serial.read());
      RY =  (Serial.read());
      mode = (Serial.read());
      fire = (Serial.read());
      for (int i=0; i<1; i++){
      byte discard = Serial.read();
      }
    
  // Serial.print(LX);
  // Serial.print(", ");
  // Serial.print(LY);
   //Serial.print(", ");
  // Serial.print(RX);
   //Serial.print(", "                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          );
  // Serial.print(RY);
   //Serial.print(", ");
  // Serial.print(mode);
   //Serial.println(" ");
  //Serial.println(fire);
  
  
  if ( mode == 1 || mode == 2)
  {
  tryb1 (LX,RY,RYB,RYF);
   myservoBT.write(90); 
   myservoLR.write(90);
  if (mode == 2)
  {
   myservoBT.write(map(LY, 0, 255, 50, 130)); 
   myservoLR.write(map(LX, 0, 255, 30, 150));
   
   if (fire == 1)
  {
   rocketCurrent = rocketCurrent + fire;
   digitalWrite (rocketCurrent, HIGH);
   //Serial.println(rocketCurrent);
   delay (5000);
   digitalWrite (rocketCurrent, LOW);
   for (int i=0; i<100; i++){
      byte discard = Serial.read();
      }
   if (rocketCurrent >12)
   {
     rocketCurrent = 7;
   
   }
  }
   //Serial.print(", ");
   //Serial.print(LY);
   //Serial.print(", ");
  // Serial.print(LX);
   //Serial.println(", ");
  }
  }
 
  
  }
  }
  

}

void tryb1 (int LX,int RY,int RYB,int RYF)
{
  if (RX > 132)
  {
  myservoSteering.write(map(RX, 132, 255, 90, 55));
   //RXR2 = map(RX, 132, 255, 0, 255);
  }
  if (RX < 123)
  {
myservoSteering.write(map(RX, 132, 0, 90, 125));
   //RXL2 = map(RX, 132, 255, 0, 255);
  }
  if (RX >= 123 && RX <= 132)
  {
    myservoSteering.write(90);

  //RXR2 =128;
  //RXL2 = 128;
  }
  
  
  
  if (RY > 132)
  {
  analogWrite(RYB, map(RY, 132, 255, 0, 254));
  digitalWrite(RYF, HIGH);
  //Serial.println(map(RY, 132, 255, 0, 254));
  }
  if (RY < 123)
  {
  analogWrite(RYB, map(RY, 123, 0, 0, 254));
  digitalWrite(RYF, LOW);
  //Serial.println(map(RY, 123, 0, 0, 254));
  }
  if (RY >= 123 && RY <= 132)
  {
  digitalWrite(RYB, LOW);
  digitalWrite(RYF, LOW);

  }
}



