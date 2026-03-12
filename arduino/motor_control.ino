#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

ESP8266WebServer server(80);

/* ================= MOTOR PINS ================= */
#define ENA D7
#define ENB D8

#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4

int motorspeed = 650;

/* ================= SERVO PINS ================= */
#define SERVO_HEAD_LR D5   // Head Left / Right
#define SERVO_HEAD_UD D6   // Head Up / Down
#define SERVO_LEFT_HAND D0 // Left Hand
#define SERVO_RIGHT_HAND D4 // Right Hand

Servo headLR;
Servo headUD;
Servo leftHand;
Servo rightHand;

/* ================= MOTOR CONTROL ================= */

void applySpeed() {
  analogWrite(ENA, motorspeed);
  analogWrite(ENB, motorspeed);
}

void stopMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void forward() {
  applySpeed();
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  applySpeed();
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left() {
  applySpeed();
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
  applySpeed();
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

/* ================= SPEED ================= */

void speed20() {
  motorspeed = 150;
  forward();
}

void speed40() {
  motorspeed = 650;
  forward();
}

void speed80() {
  motorspeed = 1023;
  forward();
}

/* ================= PARK SEQUENCE ================= */

void parkSequence() {
  backward();
  delay(3000);

  right();
  delay(1200);

  backward();
  delay(2000);

  stopMotor();
}

/* ================= SERVO HANDLER ================= */

void handleServo() {
  if (!server.hasArg("m") || !server.hasArg("a")) {
    server.send(400, "text/plain", "Missing parameters");
    return;
  }

  String motor = server.arg("m");
  int angle = server.arg("a").toInt();
  angle = constrain(angle, 0, 180);

  if (motor == "HL") headLR.write(angle);
  else if (motor == "HU") headUD.write(angle);
  else if (motor == "LH") leftHand.write(angle);
  else if (motor == "RH") rightHand.write(angle);

  server.send(200, "text/plain", "SERVO OK");
}

/* ================= SETUP ================= */

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotor();

  /* Attach Servos */
  headLR.attach(SERVO_HEAD_LR);
  headUD.attach(SERVO_HEAD_UD);
  leftHand.attach(SERVO_LEFT_HAND);
  rightHand.attach(SERVO_RIGHT_HAND);

  headLR.write(90);
  headUD.write(90);
  leftHand.write(90);
  rightHand.write(90);

  WiFi.softAP("CAR_SPEED", "1234567899");

  /* Motor Routes */
  server.on("/F", [](){ forward(); server.send(200,"text/plain","FORWARD"); });
  server.on("/B", [](){ backward(); server.send(200,"text/plain","BACKWARD"); });
  server.on("/L", [](){ left(); server.send(200,"text/plain","LEFT"); });
  server.on("/R", [](){ right(); server.send(200,"text/plain","RIGHT"); });
  server.on("/S", [](){ stopMotor(); server.send(200,"text/plain","STOP"); });

  /* Speed Routes */
  server.on("/20S", [](){ speed20(); server.send(200,"text/plain","20 KM/H"); });
  server.on("/40S", [](){ speed40(); server.send(200,"text/plain","40 KM/H"); });
  server.on("/80S", [](){ speed80(); server.send(200,"text/plain","80 KM/H"); });

  server.on("/P", [](){ parkSequence(); server.send(200,"text/plain","PARK"); });

  /* Servo Route */
  server.on("/SERVO", handleServo);

  server.begin();
}

/* ================= LOOP ================= */

void loop() {
  server.handleClient();
}
