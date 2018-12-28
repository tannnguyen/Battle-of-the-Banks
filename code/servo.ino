#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int val;    // variable to read the value from the analog pin
const int timeDelay = 150;
int button = 7;
int power = 8;
void setup() {
  pinMode(button, INPUT);
  pinMode(power, OUTPUT);
  digitalWrite(power, HIGH);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(25); // Start at 25
}

void loop() {
  if (digitalRead (button) ) {
  delay(200);
  // S
  dot();
  nextElement();
  dot();
  nextElement();
  dot();
  nextLetter();
  // O
  dash();
  nextElement();
  dash();
  nextElement();
  dash();
  nextLetter();
  // S
  dot();
  nextElement();
  dot();
  nextElement();
  dot();
  nextWord();
  }
}

// turn the piezo on
void on() {
  myservo.write(50);
}
// turn the off
void off() {
  myservo.write(25);
}

//implement a dot
void dot() {
  on();
  delay(timeDelay*2);
}
//implement a dash
void dash() {
  on();
  delay(timeDelay*5);
}
//delay time between dot/dash
void nextElement() {
  off();
  delay(timeDelay);
}
//delay tiem between letters
void nextLetter() {
  off();
  delay(timeDelay*3);
}
//delay between the words
void nextWord() {
  off();
  delay(timeDelay*5);
}
