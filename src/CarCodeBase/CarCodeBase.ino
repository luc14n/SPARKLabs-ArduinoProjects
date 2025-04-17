#include Servo.h  THIS DISABLES PWM ON PINS 9 AND 10 FOR SOME REASON. HOURS OF MY LIFE, GONE.
#include SoftwareSerial.h  I don't know what this disables, but it's for the bluetooth.

Servo myServo;
const int servoPin = 6;
int servoPos = 0;

const int motorPin1 = 4;
const int motorPin2 = 7;
const int enB = 11;
bool motorState = false;
bool motorForwards = true;  false is reverse, true is forwards
int motorSpeed = 0;

const int hc05State = 5;
const int rx = 3;
const int tx = 2;
SoftwareSerial mySerial(rx,tx);
String message = ;

void setup() {
   put your setup code here, to run once
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enB, OUTPUT);

  myServo.attach(servoPin);
  myServo.write(30);

  pinMode(hc05State, INPUT);
   pinMode(rx, INPUT);
   pinMode(tx, OUTPUT);

  Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  Begin serial communication with Arduino and HC-05
  mySerial.begin(9600);
  Serial.println(Initializing...);
  Serial.println(Started. Pairing now available.);
}

void runMotor(bool motorState, bool motorForwards, int motorSpeed) {
  if (motorForwards) {
    if (motorState) {
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      analogWrite(enB, motorSpeed);
    } else {
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);
    }
  } else {
    if (motorState) {
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, HIGH);
      analogWrite(enB, motorSpeed);
    } else {
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);
    }
  }
}

void loop() {
   put your main code here, to run repeatedly
   analogWrite(enB, 128);

   delay(500);

  if (mySerial.available()) {
    char incomingChar = mySerial.read();
    if (incomingChar != 'n') {
      message += String(incomingChar);
    }
    else {
      message = ;
    }
    Serial.write(incomingChar);
  }

   MOTOR MESSAGES

   Check received message and control output accordingly
  if (message == on) {
    motorState = true;
  }
  else if (message == off) {
    motorState = false;
  }

  if (message == rev) {
    motorForwards = false;
  } else if (message == fwd) {
    motorForwards = true;
  }

   if (message.length()  1)
     Serial.println(message.length());

  if (message.substring(0,1).equals(S) && message.length() = 4) {
     we've received a speed message
    String speed = message.substring(1,4);
    motorSpeed = speed.toInt();
  }

  runMotor(true, motorForwards, motorSpeed);

   SERVO MESSAGES

  if (message.substring(0,1).equals(R) && message.length() == 4) {
     we've received a servo message
    String pos = message.substring(1,4);
    servoPos = pos.toInt();
    myServo.write(servoPos);
  }

   delay(20);
}
