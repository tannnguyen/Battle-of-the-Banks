#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Include headers for SPI port and pixy camera
#include <SPI.h>
#include <Pixy.h>

int button = 11;
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
// You can also make another motor on port M2
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

const int FRONT_US = 7;
//left is looking down from the top with front farthest away, right corresponds
const int LEFT_US = 4;
const int RIGHT_US = 5;
const int BACK_US = 9;

Pixy pixy;

// stores vertical distance of object in Pixy camera
int y;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  pixy.init();
  pinMode (button, INPUT);
}

//bool movingForward = true;

void loop() {
  if (digitalRead(button) == HIGH) {
    delay(300);
    //Drive straight
    while (drivePin(FRONT_US) > 20){
      forward(80);
    }
    // essentially the loop() for arduino
    while (true) {
      while (drivePin(FRONT_US) > 30){
        forward(130);
      }
      //backward(150);
      /*
      while (drivePin(BACK_US) > 30){
        backward(130);
      }
      while (drivePin(FRONT_US) > 30){
        forward(130);
      }*/
      forward(0);
      delay(300);
      break;
    }
  }
 
}

void forward(int i) {
  leftMotor->setSpeed(i);
  leftMotor->run(FORWARD);
  
  rightMotor->setSpeed(i);
  rightMotor->run(FORWARD);

}


void backward(int i) {
  leftMotor->setSpeed(i);
  leftMotor->run(BACKWARD);
  // turn on motor

  
  rightMotor->setSpeed(i);
  rightMotor->run(BACKWARD);

}

// when lm > rm, right turn
// when rm > lm, left turn
void turnForward(int lm, int rm) {
  leftMotor->setSpeed(lm);
  leftMotor->run(FORWARD);
  // turn on motor

  
  rightMotor->setSpeed(rm);
  rightMotor->run(FORWARD);

}

void turnBackward(int lm, int rm) {
  leftMotor->setSpeed(lm);
  leftMotor->run(BACKWARD);
  // turn on motor

  
  rightMotor->setSpeed(rm);
  rightMotor->run(BACKWARD);

}

//Return distance of pin in cm
long drivePin(int pin) {
  long duration, cm;
  
  pinMode(pin, OUTPUT);
  
  digitalWrite(pin, LOW);
  delayMicroseconds(5);
  digitalWrite(pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pin, LOW);

  pinMode(pin, INPUT);
  duration = pulseIn(pin, HIGH);
  Serial.println(cm);
  cm = microsecondsToCentimeters(duration);
  return cm;
  
}


long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
