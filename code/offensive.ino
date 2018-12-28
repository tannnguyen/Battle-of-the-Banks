#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Include headers for SPI port and pixy camera
#include <SPI.h>
#include <Pixy.h>


// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
// You can also make another motor on port M2
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

Pixy pixy;

int button = 8;


// stores horizontal distance of object in Pixy camera
int x;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  AFMS.begin(); // create with default frequency 1.6KHz or pass hz value in function
  pixy.init();
  pinMode(button, INPUT);

}

void loop() {
  static int i = 0;
  // put your main code here, to run repeatedly:
    //Drive into position
    forward(150);
    delay(750);
    turnForward(150, 0);
    delay(350);
    forward(0);
    while (true) {
      if (digitalRead(button) == HIGH) {
        forward(0);
        delay(30000);
      }
    uint16_t blocks;
      // gets the number of blocks
      blocks = pixy.getBlocks();
      if (blocks) {
      // extracts horizontal position of object in pixy camera
          x = pixy.blocks[0].x;
      // object detected to the left
          if (x < 150) {
            turnForward(0, 150);
          } else if (x > 170) {
            turnBackward(0, 150);
          } else {
              forward(0);
          }
      }
    }
   
}
