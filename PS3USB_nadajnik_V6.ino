/*
 Example sketch for the PS3 USB library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <PS3USB.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
/* You can create the instance of the class in two ways */
PS3USB PS3(&Usb); // This will just create the instance
//PS3USB PS3(&Usb,0x00,0x15,0x83,0x3D,0x0A,0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

bool printAngle;
uint8_t state = 0;
int LHatX;
int LHatY;
int RHatX;
int RHatY;
int mode=1;
int r1;

void setup() {
  Serial.begin(9600);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 USB Library Started"));
}
void loop() {
  Usb.Task();
r1=0;
  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
    if (PS3.getAnalogHat(LeftHatX) > 132 || PS3.getAnalogHat(LeftHatX) < 256 || PS3.getAnalogHat(LeftHatY) > 132 || PS3.getAnalogHat(LeftHatY) < 123 || PS3.getAnalogHat(RightHatX) > 132 || PS3.getAnalogHat(RightHatX) < 123 || PS3.getAnalogHat(RightHatY) > 132 || PS3.getAnalogHat(RightHatY) < 123) {
      LHatX = PS3.getAnalogHat(LeftHatX);
      LHatY = PS3.getAnalogHat(LeftHatY);
      if (PS3.PS3Connected) { // The Navigation controller only have one joystick
        RHatX = PS3.getAnalogHat(RightHatX);
        RHatY = PS3.getAnalogHat(RightHatY);
        nadawanie(LHatX,LHatY,RHatX,RHatY,mode, r1);
        delay(55);
      }
    }
    /*
    // Analog button values can be read from almost all buttons
    if (PS3.getAnalogButton(L2) || PS3.getAnalogButton(R2)) {
      Serial.print(F("\r\nL2: "));
      Serial.print(PS3.getAnalogButton(L2));
      if (!PS3.PS3NavigationConnected) {
        Serial.print(F("\tR2: "));
        Serial.print(PS3.getAnalogButton(R2));
      }
    }
    if (PS3.getButtonClick(PS))
      Serial.print(F("\r\nPS"));

    if (PS3.getButtonClick(TRIANGLE))
      Serial.print(F("\r\nTraingle"));
    if (PS3.getButtonClick(CIRCLE))
      Serial.print(F("\r\nCircle"));
    if (PS3.getButtonClick(CROSS))
      Serial.print(F("\r\nCross"));
    if (PS3.getButtonClick(SQUARE))
      Serial.print(F("\r\nSquare"));
*/
    if (PS3.getButtonClick(UP)) {
      Serial.print(F("\r\nUp"));
      PS3.setLedOff();
      PS3.setLedOn(LED4);
      mode=4;
      nadawanie(LHatX,LHatY,RHatX,RHatY,mode, r1);
      delay(55);
    }
    if (PS3.getButtonClick(RIGHT)) {
      Serial.print(F("\r\nRight"));
      PS3.setLedOff();
      PS3.setLedOn(LED1);
      mode=1;
      nadawanie(LHatX,LHatY,RHatX,RHatY,mode, r1);
      delay(55);
    }
    if (PS3.getButtonClick(DOWN)) {
      Serial.print(F("\r\nDown"));
      PS3.setLedOff();
      PS3.setLedOn(LED2);
      mode=2;
      nadawanie(LHatX,LHatY,RHatX,RHatY,mode, r1);
      delay(55);
    }
    if (PS3.getButtonClick(LEFT)) {
      Serial.print(F("\r\nLeft"));
      PS3.setLedOff();
      PS3.setLedOn(LED3);
      mode=3;
      nadawanie(LHatX,LHatY,RHatX,RHatY,mode, r1);
      delay(55);
    }
/*
    if (PS3.getButtonClick(L1))
      Serial.print(F("\r\nL1"));
    if (PS3.getButtonClick(L3))
      Serial.print(F("\r\nL3"));
*/
    if (PS3.getButtonClick(R1)){
      r1=1;
      nadawanie(LHatX,LHatY,RHatX,RHatY,mode, r1);
    }
    //if (PS3.getButtonClick(R3))
      //Serial.print(F("\r\nR3"));
/*
    if (PS3.getButtonClick(SELECT)) {
      Serial.print(F("\r\nSelect - "));
      PS3.printStatusString();
    }
    if (PS3.getButtonClick(START)) {
      Serial.print(F("\r\nStart"));
      printAngle = !printAngle;
    }
    if (printAngle) {
      Serial.print(F("\r\nPitch: "));
      Serial.print(PS3.getAngle(Pitch));
      Serial.print(F("\tRoll: "));
      Serial.print(PS3.getAngle(Roll));
    }
    */
  }

 /* 
  else if (PS3.PS3MoveConnected) { // One can only set the color of the bulb, set the rumble, set and get the bluetooth address and calibrate the magnetometer via USB
    if (state == 0) {
      PS3.moveSetRumble(0);
      PS3.moveSetBulb(Off);
    } else if (state == 1) {
      PS3.moveSetRumble(75);
      PS3.moveSetBulb(Red);
    } else if (state == 2) {
      PS3.moveSetRumble(125);
      PS3.moveSetBulb(Green);
    } else if (state == 3) {
      PS3.moveSetRumble(150);
      PS3.moveSetBulb(Blue);
    } else if (state == 4) {
      PS3.moveSetRumble(175);
      PS3.moveSetBulb(Yellow);
    } else if (state == 5) {
      PS3.moveSetRumble(200);
      PS3.moveSetBulb(Lightblue);
    } else if (state == 6) {
      PS3.moveSetRumble(225);
      PS3.moveSetBulb(Purple);
    } else if (state == 7) {
      PS3.moveSetRumble(250);
      PS3.moveSetBulb(White);
    }

  
    state++;
    if (state > 7)
      state = 0;
    delay(1000);
  }
  */
}

void nadawanie (char xbee2,char xbee3,char xbee4,char xbee5, char xbee6, char xbee7){
  Serial.write(0xC8);
  Serial.write((byte)0);
  Serial.write(xbee2);
  Serial.write(xbee3);
  Serial.write(xbee4);
  Serial.write(xbee5);
  Serial.write(xbee6);
  Serial.write(xbee7);
  Serial.write((byte)0);
}
