#define RightPWM 9
#define LeftPWM 10

#define LMInput1 7
#define LMInput2 6
#define RMInput1 5
#define RMInput2 4

// rearranged some of your wiring to fit into buggy, but all is the same

void setRightPower(int power);
void setLeftPower(int power);
void setPower(int power);

void leftDirection(bool direction);
void rightDirection(bool direction);

void forward();
void backwards();
void left();
void right(); 

void setup() {
  Serial.begin(9600);

  pinMode(RightPWM, OUTPUT);
  pinMode(LeftPWM, OUTPUT);

  pinMode(LMInput1, OUTPUT);
  pinMode(LMInput2, OUTPUT);
  pinMode(RMInput1, OUTPUT);
  pinMode(RMInput2, OUTPUT);
}

void loop() {

}

void setPower(int power) {
  analogWrite(RightPWM, power);
  analogWrite(LeftPWM, power);
}

void setRightPower(int power) {
  analogWrite(RightPWM, power);
}

void setLeftPower(int power) {
  analogWrite(LeftPWM, power);
}

void leftDirection(bool direction) {
  if (direction == 1) {
    digitalWrite(LMInput1, HIGH);
    digitalWrite(LMInput2, LOW); // one direction (make sure it is forwards)
  } else {
    digitalWrite(LMInput1, LOW);
    digitalWrite(LMInput2, HIGH); // other direction (make sure it is backwards)
  }
}

void rightDirection(bool diretion) {
  // same code as above, but with right inputs
}

void forward() {
  // need both motors to be going forward, use leftDirection and rightDirection functions
}

void backward() {
  // need both motors to be going backwards, same as above but flipped
}

void left() {
  // need right motor to be going forwards and left motor to be going backwards
}

void right() {
  // need left motor to be going forwards and right motor to be going backwards
}
