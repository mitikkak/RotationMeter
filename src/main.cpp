#include "Arduino.h"
#include <LiquidCrystal.h>
#include "Rotation.h"
#include "Message.h"

const int RS = 12;
const int ENABLE = 11;
const int D4 = 7;
const int D5 = 5;
const int D6 = 3;
const int D7 = 2;
LiquidCrystal lcd(RS, ENABLE, D4, D5, D6, D7);

const int hallSensor = A1;

void setup() {
  lcd.begin(16, 2);
  lcd.print("RotationMeter");
  pinMode(hallSensor, INPUT);
  lcd.setCursor(0, 1);
}

unsigned long prevTimeLcdRefreshed = 0;
unsigned long const lcdRefreshRate = 500;
int times = 0;

Rotation rotation;

void loop() {
  times++;
  unsigned long const timeNow = millis();
  const int value = analogRead(hallSensor);
  rotation.inputSensorValue(value);
  unsigned long const deltaTime = timeNow-prevTimeLcdRefreshed;
  if (deltaTime >= lcdRefreshRate)
  {
      prevTimeLcdRefreshed = timeNow;
      lcd.clear();
      Message m1;
      Message m2;
      m2.push(rotation.times());
      m1.push(rotation.perMinute(deltaTime));
      m2.push(rotation.lowest());
      m2.final(rotation.highest());
      lcd.print(m1);
      lcd.setCursor(0, 1);
      lcd.print(m2);
      times = 0;
      rotation.init();


  }
}

