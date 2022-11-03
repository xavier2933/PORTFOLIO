//This code was developed by me for my freshman projects class. Our project was a
//rainwater power generator that would sit in a gutter and produce enough power to
//charge a cell phone or boil water. This code takes voltage readings from our 
//generator and averages them calculates our total production in Watts.

const int numreadings = 10;  //initialize variables
float readings[numreadings];
int readIndex = 0;
float total = 0.0;
float average = 0.0;
float maxvoltage = 0.0;
float current = 0;
float Watts = 0;
float WattHours = 0;

#include <LiquidCrystal.h> //include LCD library
LiquidCrystal lcd(12, 10, 5, 4, 3, 2);
const int inputpin = A2;

void setup() {
  lcd.begin(16, 2);
  for (int i = 0; i < numreadings; i++) { //Make sure all values are zero
    readings[i] = 0;
  }

}

void loop() {
  float sensorvalue = analogRead(inputpin); //Read data
  float voltage = sensorvalue * (15.0 / 1023.0); //
  String avgstring = String(average, 5);
  String voltstring = String(maxvoltage, 5);
  String watthrs = String(Watts, 5);
  if (voltage > 0) {
    total = total - float(readings[readIndex]); // Remove old readings from Total (avg) calculation

    readings[readIndex] = voltage; // Place new reading into the average voltage array
    total = total + voltage; // Replace old reading with the new...
    readIndex = readIndex + 1;

    if (readIndex >= numreadings) {
      readIndex = 0;
    }
    average = total / float(numreadings); // Calculate the new average
    maxvoltage = max(voltage, maxvoltage);
    
    lcd.setCursor(0, 0); //Print data to screen
    lcd.print("Avg Volts:");
    lcd.setCursor(10, 0);
    lcd.print(avgstring);
    
    current = maxvoltage/30;
    Watts = current * maxvoltage;
    
    lcd.setCursor(0, 1);
    lcd.print("Watt Hrs:");
    lcd.setCursor(10, 1);
    lcd.print(watthrs);
    
    delay(250);

  }

  else{
  }
}
