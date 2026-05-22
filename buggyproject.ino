#define RightPWM 9
#define LeftPWM 10

#define LMInput1 7
#define LMInput2 6
#define RMInput1 5
#define RMInput2 4

void setRightPower(int power);
void setLeftPower(int power);
void setPower(int power);

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

void forward() {
  ;
}

void backward() {
  ;
}

void left() {
  ;
}

void right() {
  ;
}
