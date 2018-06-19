
#include "Components.h"

void setup() {
  lcd.begin(16, 2);
  lcd.print("RotationMeter");
  pinMode(hallSensor, INPUT);
  lcd.setCursor(0, 1);
  Serial.begin(9600);
}

