#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define greenButton 2
#define blueButton  3
#define redButton   4

#define greenLED 8
#define blueLED  9
#define redLED   10

int lcdI2CAddress = 0x20;
int lcdCols = 16;
int lcdRows = 2;

LiquidCrystal_I2C lcd(lcdI2CAddress, lcdCols, lcdRows);

const int GAME_LENGTH = 10;

int lowWait = 1000;
int highWait = 5000;
int ledOnDuration = 3000;

int phase2LowWait = 700;
int phase2HighWait = 3500;
int phase2LedOnDuration = 2000;

int phase3LowWait = 450;
int phase3HighWait = 2200;
int phase3LedOnDuration = 1200;

int phase4LowWait = 250;
int phase4HighWait = 1200;
int phase4LedOnDuration = 700;

int phase2Threshold = 20000;
int phase3Threshold = 35000;
int phase4Threshold = 50000;

int countdownSeconds = 3;
int resultDisplayMillis = 600;

int score = 0;
int currentRound = 0;
long gameStartMillis = 0;
long allReactions[GAME_LENGTH];


String chooseColor();
void waitRandomMillis(int low, int high);
void turnOffAllLEDs();
void showResults();
void getCurrentPhaseWaits(int &low, int &high, int &onDuration);
void lcdTopBottom(String top, String bottom);
int getCurrentPhase();


void setup() {
  Serial.begin(9600);

  pinMode(greenButton, INPUT_PULLUP);
  pinMode(blueButton, INPUT_PULLUP);
  pinMode(redButton, INPUT_PULLUP);

  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  lcd.init();
  lcd.backlight();

  randomSeed(analogRead(6));

  lcdTopBottom("  Reaction Game", "   Get Ready!");
  delay(1500);

  for (int i = countdownSeconds; i > 0; i--) {
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("Ready?");
    lcd.setCursor(7, 1);
    lcd.print(i);
    delay(1000);
  }

  lcdTopBottom("      GO!", "");
  delay(600);

  gameStartMillis = millis();
}


void loop() {
  while (currentRound < GAME_LENGTH) {
    int currentLow, currentHigh, currentOnDuration;
    getCurrentPhaseWaits(currentLow, currentHigh, currentOnDuration);

    int phase = getCurrentPhase();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Round ");
    lcd.print(currentRound + 1);
    lcd.print("/");
    lcd.print(GAME_LENGTH);
    lcd.setCursor(0, 1);
    lcd.print("Score: ");
    lcd.print(score);
    lcd.print("  Lv");
    lcd.print(phase);

    waitRandomMillis(currentLow, currentHigh);

    String currentColor = chooseColor();
    long reactionSpeed = 0;
    bool scored = false;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Press: ");
    lcd.print(currentColor);

    long ledOnStart = millis();

    if (currentColor == "RED") {
      digitalWrite(redLED, HIGH);
      while (millis() - ledOnStart < currentOnDuration) {
        if (digitalRead(redButton) == LOW) {
          reactionSpeed = millis() - ledOnStart;
          score++;
          scored = true;
          break;
        }
      }
      digitalWrite(redLED, LOW);

    } else if (currentColor == "BLUE") {
      digitalWrite(blueLED, HIGH);
      while (millis() - ledOnStart < currentOnDuration) {
        if (digitalRead(blueButton) == LOW) {
          reactionSpeed = millis() - ledOnStart;
          score++;
          scored = true;
          break;
        }
      }
      digitalWrite(blueLED, LOW);

    } else {
      digitalWrite(greenLED, HIGH);
      while (millis() - ledOnStart < currentOnDuration) {
        if (digitalRead(greenButton) == LOW) {
          reactionSpeed = millis() - ledOnStart;
          score++;
          scored = true;
          break;
        }
      }
      digitalWrite(greenLED, LOW);
    }

    allReactions[currentRound] = scored ? reactionSpeed : -1;

    if (scored) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Hit! ");
      lcd.print(reactionSpeed);
      lcd.print("ms");
      lcd.setCursor(0, 1);
      lcd.print("Score: ");
      lcd.print(score);

      Serial.print("Round ");
      Serial.print(currentRound + 1);
      Serial.print(" | Hit! ");
      Serial.print(reactionSpeed);
      Serial.print("ms | Score: ");
      Serial.println(score);
    } else {
      lcdTopBottom("    Missed!", "Score: " + String(score));

      Serial.print("Round ");
      Serial.print(currentRound + 1);
      Serial.print(" | Missed | Score: ");
      Serial.println(score);
    }

    currentRound++;
    delay(resultDisplayMillis);
  }

  turnOffAllLEDs();
  showResults();

  while (true) {}
}


int getCurrentPhase() {
  long elapsed = millis() - gameStartMillis;
  if (elapsed >= phase4Threshold) return 4;
  if (elapsed >= phase3Threshold) return 3;
  if (elapsed >= phase2Threshold) return 2;
  return 1;
}


void getCurrentPhaseWaits(int &low, int &high, int &onDuration) {
  int phase = getCurrentPhase();
  if (phase == 4) {
    low = phase4LowWait;  
    high = phase4HighWait;  
    onDuration = phase4LedOnDuration;
  } else if (phase == 3) {
    low = phase3LowWait;  
    high = phase3HighWait;  
    onDuration = phase3LedOnDuration;
  } else if (phase == 2) {
    low = phase2LowWait;  
    high = phase2HighWait;  
    onDuration = phase2LedOnDuration;
  } else {
    low = lowWait;        
    high = highWait;         
    onDuration = ledOnDuration;
  }
}


String chooseColor() {
  int randNum = random(0, 3);
  if (randNum == 0) return "RED";
  if (randNum == 1) return "BLUE";
  return "GREEN";
}


void waitRandomMillis(int low, int high) {
  delay(random(low, high));
}


void turnOffAllLEDs() {
  digitalWrite(redLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(greenLED, LOW);
}


void lcdTopBottom(String top, String bottom) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(top);
  lcd.setCursor(0, 1);
  lcd.print(bottom);
}


void showResults() {
  long total = 0;
  long fastest = -1;
  long slowest = -1;
  int hits = 0;

  for (int i = 0; i < GAME_LENGTH; i++) {
    if (allReactions[i] != -1) {
      total += allReactions[i];
      hits++;
      if (fastest == -1 || allReactions[i] < fastest) fastest = allReactions[i];
      if (slowest == -1 || allReactions[i] > slowest) slowest = allReactions[i];
    }
  }

  long avgReaction = (hits > 0) ? (total / hits) : 0;

  Serial.println("\n===== GAME OVER =====");
  for (int i = 0; i < GAME_LENGTH; i++) {
    Serial.print("Round ");
    Serial.print(i + 1);
    Serial.print(": ");
    if (allReactions[i] == -1) {
      Serial.println("Missed");
    } else {
      Serial.print(allReactions[i]);
      Serial.println("ms");
    }
  }
  Serial.print("Final Score: ");
  Serial.print(score);
  Serial.print(" / ");
  Serial.println(GAME_LENGTH);
  if (hits > 0) {
    Serial.print("Avg: ");     
    Serial.print(avgReaction); 
    Serial.println("ms");
    Serial.print("Fastest: "); 
    Serial.print(fastest);     
    Serial.println("ms");
    Serial.print("Slowest: "); 
    Serial.print(slowest);     
    Serial.println("ms");
  }
  Serial.println("Reset to play again!");

  lcdTopBottom("   Game Over!", "Score: " + String(score) + "/" + String(GAME_LENGTH));
  delay(2500);

  if (hits > 0) {
    lcdTopBottom("Avg: " + String(avgReaction) + "ms", "Best: " + String(fastest) + "ms");
    delay(2500);
    lcdTopBottom("Slowest:", String(slowest) + "ms");
    delay(2500);
  }

  String scoreMsg;
  if (score == GAME_LENGTH) {scoreMsg = "Perfect score!";}
  else if (score >= GAME_LENGTH * 0.8) {scoreMsg = "Great job!";}
  else if (score >= GAME_LENGTH * 0.5) {scoreMsg = "Not bad!";}
  else {scoreMsg = "Keep trying!";}

  lcdTopBottom(scoreMsg, "Reset to replay");
}
