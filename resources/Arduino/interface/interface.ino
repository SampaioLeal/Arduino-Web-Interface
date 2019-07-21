#include <LiquidCrystal.h>
#include "StringSplitter.h"
#include <Servo.h>

#define SERVO 6 // Porta Digital 6 PWM

Servo s; // Variável Servo

LiquidCrystal lcd(50, 51, 48, 49, 52, 53);

char key;
String value;

void setup()
{
  Serial.begin(9600);
  //Define o número de colunas e linhas do LCD
  lcd.begin(16, 2);
  s.attach(SERVO);
  s.write(0);
}

void loop()
{
  value = "";
  if (Serial.available() > 0) {
    do {
      key = Serial.read(); // read it and store it in val
      if (key != -1) {
        value = value + key;
      }
    } while (key != -1);

    StringSplitter *splitter = new StringSplitter(value, '.', 3);
    String line1 = splitter->getItemAtIndex(0);
    String line2 = splitter->getItemAtIndex(1);
    int pos = splitter->getItemAtIndex(2).toInt();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(line1);
    lcd.setCursor(0, 1);
    lcd.print(line2);

    s.write(pos);

    delay(2000);
  }
}
