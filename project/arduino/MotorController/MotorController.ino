int motor1pin1 = 9; // OUT3 Positive
int motor1pin2 = 10; // OUT4 Negative
int motor1speed = 8; // ENB pin

int motor2pin1 = 11; // OUT2 Positve
int motor2pin2 = 12; // OUT1 Negative
int motor2speed = 13; //ENA pin

void setup() {
  // put your setup code here, to run once:

  // Initializing Motor Pins
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1,  OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  // Initializing Motor Speed Pins
  pinMode(motor1speed,  OUTPUT); 
  pinMode(motor2speed, OUTPUT);
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
