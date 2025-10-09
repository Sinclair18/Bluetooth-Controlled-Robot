#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(4, 3);

struct Motor {
  uint8_t ENPin;
  uint8_t INPin1;
  uint8_t INPin2;
};
int maxSpeed = 255, avSpeed = 128, buzzPin = 12;

Motor Motors[] = {
  { 10, 9, 8 },
  { 5, 7, 2 },
  { 6, A2, A3 },
  { 11, A1, A0 }
};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Bluetooth.begin(9600);

  for (int i = 0; i < sizeof(Motors) / sizeof(Motors[0]); i++) {
    pinMode(Motors[i].ENPin, OUTPUT);
    pinMode(Motors[i].INPin1, OUTPUT);
    pinMode(Motors[i].INPin2, OUTPUT);
  }
  tone(buzzPin, 1000);
  delay(700);
  noTone(buzzPin);
}

void loop() {
  bool soundOn = false;
  unsigned long soundStart = 0;
  const int validSoundDuration = 200;

  while (Bluetooth.available()) {
    char command = Bluetooth.read();
    Serial.print("Received: ");
    Serial.print(command);
    Serial.print("\n\n");

    switch (command) {
      case 'F':
        moveForward();
        break;

      case 'B':
        moveBackward();
        break;

      case 'L':
        turnLeft();
        break;

      case 'R':
        turnRight();
        break;

      case 'S':
        stop();
        break;

      case 'G':
        forwardLeft();
        break;

      case 'H':
        backwardLeft();
        break;

      case 'I':
        forwardRight();
        break;

      case 'J':
        backwardRight();
        break;

      case 'V':
        tone(buzzPin, 200);
        soundOn = true;
        soundStart = millis();
        break;

      default:
        noTone(buzzPin);
    }

    if(soundOn && (millis() - soundStart >= validSoundDuration)){
      noTone(buzzPin);
      soundOn = false;
    }
  }
}


void moveForward() {  // All motors rotate backwards
  for (int i = 0; i < sizeof(Motors) / sizeof(Motors[0]); i++) {
    analogWrite(Motors[i].ENPin, avSpeed);
    digitalWrite(Motors[i].INPin1, HIGH);
    digitalWrite(Motors[i].INPin2, LOW);
  }
}


void moveBackward() {  // All motors rotate backwards
  for (int i = 0; i < sizeof(Motors) / sizeof(Motors[0]); i++) {
    analogWrite(Motors[i].ENPin, avSpeed);
    digitalWrite(Motors[i].INPin1, LOW);
    digitalWrite(Motors[i].INPin2, HIGH);
  }
}


void turnRight() {  // Left motors rotate forward and Right motors rotate backwards
  for (int i = 0; i < sizeof(Motors) / sizeof(Motors[0]); i++) {
    analogWrite(Motors[i].ENPin, avSpeed);
  }

  digitalWrite(Motors[0].INPin1, LOW);
  digitalWrite(Motors[0].INPin2, HIGH);

  digitalWrite(Motors[1].INPin1, HIGH);
  digitalWrite(Motors[1].INPin2, LOW);

  digitalWrite(Motors[2].INPin1, HIGH);
  digitalWrite(Motors[2].INPin2, LOW);

  digitalWrite(Motors[3].INPin1, LOW);
  digitalWrite(Motors[3].INPin2, HIGH);
}  // EOF


void forwardRight() {  // Left motors rotate forward and Right motors stop
  analogWrite(Motors[0].ENPin, 0);
  analogWrite(Motors[1].ENPin, 255);
  analogWrite(Motors[2].ENPin, 255);
  analogWrite(Motors[3].ENPin, 0);

  digitalWrite(Motors[1].INPin1, HIGH);  // Motor 1
  digitalWrite(Motors[1].INPin2, LOW);

  digitalWrite(Motors[2].INPin1, HIGH);  // Motor 4
  digitalWrite(Motors[2].INPin2, LOW);
}  // EOF


void backwardRight() {  // Left motors rotate backwards and Right motors stop
  analogWrite(Motors[0].ENPin, 0);
  analogWrite(Motors[1].ENPin, 255);
  analogWrite(Motors[2].ENPin, 255);
  analogWrite(Motors[3].ENPin, 0);

  digitalWrite(Motors[1].INPin1, LOW);  // Motor 1
  digitalWrite(Motors[1].INPin2, HIGH);

  digitalWrite(Motors[2].INPin1, LOW);  // Motor 4
  digitalWrite(Motors[2].INPin2, HIGH);
}  // EOF


void turnLeft() {  // Left motors rotate backwards and Right motors rotate forward
  for (int i = 0; i < sizeof(Motors) / sizeof(Motors[0]); i++) {
    analogWrite(Motors[i].ENPin, avSpeed);
  }

  digitalWrite(Motors[0].INPin1, HIGH);
  digitalWrite(Motors[0].INPin2, LOW);

  digitalWrite(Motors[1].INPin1, LOW);
  digitalWrite(Motors[1].INPin2, HIGH);

  digitalWrite(Motors[2].INPin1, LOW);
  digitalWrite(Motors[2].INPin2, HIGH);

  digitalWrite(Motors[3].INPin1, HIGH);
  digitalWrite(Motors[3].INPin2, LOW);
}  // EOF

void forwardLeft() {  // Left motors stop and Right motors rotate forward
  analogWrite(Motors[0].ENPin, 255);
  analogWrite(Motors[1].ENPin, 0);
  analogWrite(Motors[2].ENPin, 0);
  analogWrite(Motors[3].ENPin, 255);

  digitalWrite(Motors[0].INPin1, HIGH);  // Motor 1
  digitalWrite(Motors[0].INPin2, LOW);

  digitalWrite(Motors[3].INPin1, HIGH);  // Motor 4
  digitalWrite(Motors[3].INPin2, LOW);
}  // EOF


void backwardLeft() {  // Left motors stop and Right motors rotate backward
  analogWrite(Motors[0].ENPin, 255);
  analogWrite(Motors[1].ENPin, 0);
  analogWrite(Motors[2].ENPin, 0);
  analogWrite(Motors[3].ENPin, 255);

  digitalWrite(Motors[1].INPin1, LOW);  // Motor 1
  digitalWrite(Motors[1].INPin2, HIGH);

  digitalWrite(Motors[2].INPin1, LOW);  // Motor 4
  digitalWrite(Motors[2].INPin2, HIGH);
}  // EOF


void stop() {  // The enable pins of all motors are disabled
  for (int i = 0; i < sizeof(Motors) / sizeof(Motors[0]); i++) {
    analogWrite(Motors[i].ENPin, 0);
  }
}  // EOF
