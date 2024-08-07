#define TX2 17
#define RX2 16

#include <WiFi.h>
#include <WiFiClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int BuzzerPin = 2;
int ledgreen = RX2;
int ledred = TX2;
int fan = 5;
int sensor = 26;
float gas = 0;
bool perigo = false;

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(ledgreen, OUTPUT);
  pinMode(ledred, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(BuzzerPin, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(1, 0);
  lcd.print("Detector de Gas");
  delay(1500);
  lcd.setCursor(0, 1);
  lcd.print("--------------------");
  delay(1000);
  lcd.clear();
}

void loop() {
  gas = analogRead(sensor);
  gas = gas * 100 / 4095;

  lcd.setCursor(0, 0);
  lcd.print("NIVEL= ");
  lcd.print(gas);
  lcd.print(" %   ");
  lcd.setCursor(0, 1);

  if (gas > 50 && !perigo) {
    perigo = true;
    digitalWrite(BuzzerPin, HIGH);
    digitalWrite(ledred, HIGH);
    digitalWrite(ledgreen, LOW);
    digitalWrite(fan, HIGH);
    lcd.print("PERIGO!!!");
  } else if (gas <= 50 && perigo) {
    perigo = false;
    digitalWrite(BuzzerPin, LOW);
    digitalWrite(ledred, LOW);
    digitalWrite(ledgreen, HIGH);
    digitalWrite(fan, LOW);
    lcd.print("SEM PERIGO     ");
  }
}
