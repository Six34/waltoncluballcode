

#define greenButton 2
#define blueButton 3
#define redButton 4

#define greenLED 8
#define blueLED 9
#define redLED 10

String currentColor = NULL; // just nothing at start

const int gameLength = 10;
int score = 0;
int currentRound = 0;

int lowWaitMillis = 1000;
int highWaitMillis = 5000;

bool gameRunning = true;
bool LEDSHowing = false;

int reactionSpeed = 0;

int allReactions[gameLength];

String chooseColor();

void waitRandomMillis(int low, int high);

void setup() {
  pinMode(greenButton, INPUT_PULLUP);
  pinMode(blueButton, INPUT_PULLUP);
  pinMode(redButton, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (currentRound < gameLength && gameRunning = true) {
    gameRunning = true;
    // wait random amount of time (using function)
    // choose an LED color
    // read how long it takes for the person to press
    // make sure to change all the variables that need to change 
    // make sure to turn the correct LED on/off

    currentColor = chooseColor;
    if (currentColor == "RED") {
      digitalWrite(redLED, HIGH);
      long startReactMillis = millis();
      while (digitalRead(redButton == HIGH)) {
        ;
      }
      long endReactMillis = millis();

      reactionSpeed = endReactMillis - startReactMillis;
      allReactions[currentRound] = reactionSpeed; // storing latest reaction
    } // ^^ copy paste this code above for the other 2 colors and make sure to change it accordingly
  }
  gameRunning = false;

  // add a display perhaps? << in class if finished early.


}

String chooseColor(){
  int randNum = random(1, 3);
  if (randNum == 1) {
    return "RED";
  } else if (randNum == 2) {
    return "BLUE";
  } else {
    return "GREEN";
  }
}

void waitRandomMillis(int low, int high) {
  waiting = true;
  randomTimeMillis = random(low, high);

  delay(randomTimeMillis);

  waiting = false;
}
