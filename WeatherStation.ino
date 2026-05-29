#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 16, 2);

int ldrPin = A0;
int micPin = A1;

void setup() {
  lcd.init();
  lcd.backlight();
}

void loop() {
  int lightValue = analogRead(ldrPin);

  long micTotal = 0;
  int samples = 0;

  unsigned long startTime = millis();

  while (millis() - startTime < 1000) {
    micTotal += analogRead(micPin);
    samples++;
  }

  int micAverage = micTotal / samples;

  int lightPercent = map(lightValue, 0, 1023, 0, 100);
  int windPercent = map(micAverage, 0, 1023, 0, 100);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Light: ");
  lcd.print(lightPercent);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Wind: ");
  lcd.print(windPercent);
  lcd.print("%");
}