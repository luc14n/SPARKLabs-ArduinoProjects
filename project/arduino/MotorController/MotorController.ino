// Motor Cluster: pins 8-13
int motor1pin1 = 8; // OUT3 Positive
int motor1pin2 = 11; // OUT4 Negative
int motor1speed = 9; // ENB pin
int motor2pin1 = 12; // OUT2 Positve
int motor2pin2 = 13; // OUT1 Negative
int motor2speed = 10; //ENA pin

// Input Cluster: 
int lightsensRIGHTpin = A3; // ANALOG
int lightsensLEFTpin = A2; // ANALOG
// -> Digital Inputs:
int potentiometerpin = 3; // DIGITAL
int startButtonpin = 6; // DIGITAL

// Output Cluster:
int signalLEDpin = 7; // DIGITAL

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:

  // Initializing Motor Pins
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1,  OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  // Initializing Motor Speed Pins
  pinMode(motor1speed,  OUTPUT); 
  pinMode(motor2speed, OUTPUT);

  // Initializing Digital Inputs
  pinMode(startButtonpin, INPUT);
  pinMode(potentiometerpin, INPUT);
  pinMode(lightsensRIGHTpin, INPUT);
  pinMode(lightsensLEFTpin, INPUT);

  // Initializing Digital Outputs
  pinMode(signalLEDpin, OUTPUT);

  // While loop to hold before button press
  digitalWrite(signalLEDpin, HIGH);
  int controlButtonStatus = LOW;
  while (true) {
    delay(10);
    controlButtonStatus = digitalRead(startButtonpin);
    if (controlButtonStatus == HIGH) {
      digitalWrite(signalLEDpin, LOW);
      loop();
    }
    if (analogRead(lightsensLEFTpin) || analogRead(lightsensRIGHTpin)) {

    }
    // Write potentiometer to light sensors
    //digitalWrite();

  }
}

void loop() {
  // put your main code here, to run repeatedly:
  //Controlling speed (0  = off and 255 = max speed):
  analogWrite(motor1speed, 255); 
  analogWrite(motor2speed, 255); 

  // Both Run the same direction set up like this. WARNING flipping motors will flip directions.
  digitalWrite(motor1pin1,  HIGH);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1,  HIGH);
  digitalWrite(motor2pin2, LOW);
}

