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
int potentiometerpin = A1; // ANALOG
int startButtonpin = 6; // DIGITAL

// Output Cluster:
int signalLEDpin = 7; // DIGITAL
const int PRESET_SENSITIVITY = 25;

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

  config();
}

void config() {
  int controlButtonStatus = LOW;
  int adjLightReadRight;
  int adjLightReadLeft;
  int adjPoten;
  while (true) {
    delay(300);
    controlButtonStatus = digitalRead(startButtonpin);
    if (controlButtonStatus == HIGH) {
      digitalWrite(signalLEDpin, LOW);
      delay(1000);
      break;
    }
    if (adjLightReadRight < PRESET_SENSITIVITY || adjLightReadLeft < PRESET_SENSITIVITY ) {
      digitalWrite(signalLEDpin, HIGH);
    } else {
      digitalWrite(signalLEDpin, LOW);
    }
    
    adjPoten = map(analogRead(potentiometerpin), 0, 1023, 500, 5000);
    adjLightReadRight = map((long) (analogRead(lightsensRIGHTpin) * (adjPoten / 100)), 0, 1023, 1, 100);
    adjLightReadLeft = map((long) (analogRead(lightsensLEFTpin) * (adjPoten / 100)), 0, 1023, 1, 100);
    // Serial.print(adjLightReadRight);
    // Serial.print("\n");
    // Serial.print(adjLightReadLeft);
    // Serial.print("\n");
    Serial.print("poten: ");
    Serial.print(adjPoten);
    Serial.print("\n");
    Serial.print("right: ");
    Serial.print(adjLightReadRight);
    Serial.print("\n");
    Serial.print("left: ");
    Serial.print(adjLightReadLeft);
    Serial.print("\n");


    //digitalWrite();

  }
}

int sensitivityScale;
int lightRight;
int lightLeft;

void loop() {
  // put your main code here, to run repeatedly:

  //Controlling speed (0  = off and 255 = max speed):
  // analogWrite(motor1speed, 255); 
  // analogWrite(motor2speed, 255); 

  // Both Run the same direction set up like this. WARNING flipping motors will flip directions.
  digitalWrite(motor1pin1,  HIGH);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1,  HIGH);
  digitalWrite(motor2pin2, LOW);

  delay(10);

  sensitivityScale = map(analogRead(potentiometerpin), 0, 1023, 500, 5000);
  lightRight = map((long) (analogRead(lightsensRIGHTpin) * (sensitivityScale / 100)), 0, 1023, 1, 100);
  lightLeft = map((long) (analogRead(lightsensLEFTpin) * (sensitivityScale / 100)), 0, 1023, 1, 100);

  if (lightRight < PRESET_SENSITIVITY && lightLeft < PRESET_SENSITIVITY ) {
    digitalWrite(signalLEDpin, HIGH);
  } else {
    digitalWrite(signalLEDpin, LOW);
  }

  if (digitalRead(startButtonpin) == HIGH) {
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, LOW);

    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, LOW);

    config();
  }

  if (lightRight > PRESET_SENSITIVITY && lightLeft > PRESET_SENSITIVITY) { // 0 - 0
    adjustSpeed(50, 100);
  } else if (lightRight > PRESET_SENSITIVITY && lightLeft <= PRESET_SENSITIVITY) { // 0 - 1
    adjustSpeed(100, 30);
  } else if (lightRight <= PRESET_SENSITIVITY && lightRight > PRESET_SENSITIVITY) { // 1 - 0
    adjustSpeed(75, 100);
  } else { // 1 - 1
    adjustSpeed(100, 50);
  }

}

void adjustSpeed(int left, int right) {
  analogWrite(motor1speed, map(right, 0, 100, 50, 255)); 
  analogWrite(motor2speed, map(left, 0, 100, 50, 255)); 
}
