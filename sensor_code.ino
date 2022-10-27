#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int redPin = 8;
const int greenPin = 7;
const int bluePin = 6;
float calibrationconstant = 0;
float calibrationcoefficient = 1;
float dt = 1;
float Concentration = 0;
float reference = 5.0;

void setup() {
  pinMode (redPin, OUTPUT);
  pinMode (greenPin, OUTPUT);
  pinMode (bluePin, OUTPUT);
  pinMode (A0, INPUT);
  Serial.begin (9600);
  lcd.begin ();
  float photoValueInitial = analogRead (A0);
  calibrationconstant = (photoValueInitial*reference)/1023;
  //add calibration coefficient
}

void loop() {
  setColor (255, 0, 0);
  Serial.print ("Concentration -> ");
  printValue ();
  lcd.setCursor(0,0);
  lcd.print ("O3");
}

void setColor (int redValue, int greenValue, int blueValue) {
  analogWrite (redPin, redValue);
  analogWrite (greenPin, greenValue);
  analogWrite (bluePin, blueValue);
}

void printValue () {
  float photoValueInitial = analogRead (A0);
  float photoValue = (photoValueInitial*reference)/1023;
  Concentration = (photoValue-calibrationconstant)/calibrationcoefficient;
  
  Serial.println (photoValueInitial);
  lcd.setCursor(0,0);
  lcd.print (Concentration);
  delay (3000);
}
