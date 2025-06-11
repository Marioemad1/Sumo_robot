int TRIG = 2;
int ECHO = 3;
int ir = 6;

int ENA1 = 11;
int IN1 = 10;
int IN2 = 9;
int IN3 = 8;
int IN4 = 7;
int ENB = 12;

int dir_speed = 200;

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(ir, INPUT);
  pinMode(ENA1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  long duration;
  int distance;
  int stop_line = digitalRead(ir);

  // --- Trigger the ultrasonic ---
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // --- Get duration & convert to cm ---
  duration = pulseIn(ECHO, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm\tIR: ");
  Serial.println(stop_line);

  // --- Main logic ---
  if (stop_line == 1) {
    // 🟥 Line detected – GO BACKWARD
    analogWrite(ENA1, dir_speed);
    analogWrite(ENB, dir_speed);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH); // Left motor reverse
    digitalWrite(IN3, HIGH); // Right motor reverse
    digitalWrite(IN4, LOW);

    delay(500); // reverse for 0.5 seconds

    // Optional: rotate to reposition
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(300); // rotate slightly
  }
  else if (distance < 25 && distance > 0) {
    // 🟨 Enemy detected – PUSH FORWARD
    analogWrite(ENA1, dir_speed);
    analogWrite(ENB, dir_speed);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  else {
    // 🟦 No enemy – SPIN and search
    analogWrite(ENA1, dir_speed);
    analogWrite(ENB, dir_speed);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }

  delay(100);
}
