#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LiquidCrystal_I2C.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

LiquidCrystal_I2C lcd(0x20, 16, 2);

const int knobPin = A0;
const int speakerPin = 8;

int frequency = 0;

void setup() {
  Serial.begin(9600);

  pinMode(speakerPin, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Frequency:");
}

void loop() {

  int knobValue = analogRead(knobPin);
  Serial.println(knobValue);

  frequency = map(knobValue, 0, 1023, 200, 800);

  tone(speakerPin, frequency);

  lcd.setCursor(0, 1);
  lcd.print("                "); 
  lcd.setCursor(0, 1);
  lcd.print(frequency);
  lcd.print(" Hz");

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Square Wave");

  int yHigh = 20;
  int yLow = 50;

  int waveWidth = map(frequency, 100, 2000, 0, 40);

  for (int x = 0; x < SCREEN_WIDTH; x += waveWidth * 2) {

    display.drawLine(x, yHigh, x + waveWidth, yHigh, SSD1306_WHITE);

    display.drawLine(x + waveWidth, yHigh,
                     x + waveWidth, yLow, SSD1306_WHITE);

    display.drawLine(x + waveWidth, yLow,
                     x + waveWidth * 2, yLow, SSD1306_WHITE);

    display.drawLine(x + waveWidth * 2, yLow,
                     x + waveWidth * 2, yHigh, SSD1306_WHITE);
  }

  display.display();
}