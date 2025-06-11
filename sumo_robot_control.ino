#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3); //pin 2 rx and pin 3 is tx
int ENA1 = 11;  // Enable pin for motor 1 (left)
int IN1 = 10;   // Direction pin for motor 1
int IN2 = 9;

int IN3 = 8;    // Direction pin for motor 2 (right)
int IN4 = 7;
int ENB = 12;   // Enable pin for motor 2
char command;

void setup() {
  pinMode(ENA1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop() {

  if (BTSerial.available()) {
   command=BTSerial.read();
  }

  // Stop all directions first (avoid mixed directions)
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  if (command=='M') {
  
  }

  if (command=='F') {
    // Go forward
    analogWrite(ENA1, 255);
    analogWrite(ENB, 255);
    digitalWrite(IN1, HIGH);  // Motor1 forward
    digitalWrite(IN4, HIGH);  // Motor2 forward
  }
  else if (command=='R') {
    // go back
    analogWrite(ENA1, 255);
    analogWrite(ENB, 255);
    digitalWrite(IN2, HIGH);  // Motor1 backward
    digitalWrite(IN4, HIGH);  // Motor2 forward
  }
  else if (command=='L') {
    // Turn left
    analogWrite(ENA1, 255);
    analogWrite(ENB, 255);
    digitalWrite(IN1, HIGH);  // Motor1 forward
    digitalWrite(IN3, HIGH);  // Motor2 backward
  }
  else if (command== 'B') {
    analogWrite(ENA1, 255);
    analogWrite(ENB, 255);
    digitalWrite(IN2, HIGH);  // Motor1 forward
    digitalWrite(IN3, HIGH);  // Motor2 forward
  }
  else {
    // Stop
    analogWrite(ENA1, 0);
    analogWrite(ENB, 0);
  }

  delay(100);  // small delay for stability
}
