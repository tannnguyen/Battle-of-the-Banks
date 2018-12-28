#define enA 5
#define in1 6
#define in2 7

int rotDirection = 0;
int pressed = false;
void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Set initial rotation direction
  digitalWrite(in2,LOW);
  digitalWrite(enA,HIGH);
}
void loop() {
  analogWrite(in1,110);
}
