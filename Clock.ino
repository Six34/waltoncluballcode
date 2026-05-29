#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int setButton = 2;
int addButton = 3;
int alarmButton = 4;
int buzzer = 5;

int hours = 12;
int minutes = 0;
int seconds = 0;
int alarmHour = 12;
int alarmMinute = 1;

bool alarmEnabled = false;
bool alarmTriggered = false;
bool alarmSounding = false;

unsigned long previousMillis = 0;
unsigned long alarmStartMillis = 0;

bool lastSetState = HIGH;
bool lastAddState = HIGH;
bool lastAlarmState = HIGH;

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(setButton, INPUT_PULLUP);
  pinMode(addButton, INPUT_PULLUP);
  pinMode(alarmButton, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
  lcd.clear();
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;
    seconds++;
    if (seconds >= 60) { seconds = 0; minutes++; }
    if (minutes >= 60) { minutes = 0; hours++; }
    if (hours >= 24) { hours = 0; }
  }

  bool currentSetState = digitalRead(setButton);
  if (currentSetState == LOW && lastSetState == HIGH) {
    seconds = 0;
    minutes++;
    if (minutes >= 60) { minutes = 0; hours++; }
    if (hours >= 24) { hours = 0; }
  }
  lastSetState = currentSetState;

  bool currentAddState = digitalRead(addButton);
  if (currentAddState == LOW && lastAddState == HIGH) {
    alarmMinute++;
    if (alarmMinute >= 60) { alarmMinute = 0; alarmHour++; }
    if (alarmHour >= 24) { alarmHour = 0; }
  }
  lastAddState = currentAddState;

  bool currentAlarmState = digitalRead(alarmButton);
  if (currentAlarmState == LOW && lastAlarmState == HIGH) {
    if (alarmSounding) {
      alarmSounding = false;
      alarmTriggered = true;
      digitalWrite(buzzer, LOW);
    } else {
      alarmEnabled = !alarmEnabled;
    }
  }
  lastAlarmState = currentAlarmState;

  if (alarmEnabled && hours == alarmHour && minutes == alarmMinute && seconds == 0 && !alarmTriggered) {
    alarmTriggered = true;
    alarmSounding = true;
    alarmStartMillis = currentMillis;
    digitalWrite(buzzer, HIGH);
  }

  if (alarmSounding && currentMillis - alarmStartMillis >= 5000) {
    alarmSounding = false;
    digitalWrite(buzzer, LOW);
  }

  if (hours != alarmHour || minutes != alarmMinute) {
    alarmTriggered = false;
  }

  lcd.setCursor(0, 0);
  if (hours < 10) lcd.print("0");
  lcd.print(hours);
  lcd.print(":");
  if (minutes < 10) lcd.print("0");
  lcd.print(minutes);
  lcd.print(":");
  if (seconds < 10) lcd.print("0");
  lcd.print(seconds);
  lcd.print("   ");

  lcd.setCursor(0, 1);
  lcd.print("A ");
  if (alarmHour < 10) lcd.print("0");
  lcd.print(alarmHour);
  lcd.print(":");
  if (alarmMinute < 10) lcd.print("0");
  lcd.print(alarmMinute);
  lcd.print(alarmEnabled ? " ON " : " OFF");

  delay(50);
}