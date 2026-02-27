#include <LiquidCrystal_I2C.h>
#include <math.h>

#define RT0 10000        // Nominal resistance at 25 ºC
#define B 3977           // Beta coefficient of the thermistor
#define R 10000          // Series resistor value
#define T0 298.15        // Nominal temperature in Kelvin (25 ºC)

// Initialize LCD with I2C address 0x27, 16 columns, 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);  

// Variables
float RT, VR, ln, TX, VRT;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  // Read voltage across thermistor
  VRT = (5.00 / 1023.00) * analogRead(A0);
  
  // Voltage across series resistor
  VR = 5.00 - VRT;

  // Calculate resistance of thermistor
  RT = VRT / (VR / R);

  // Calculate temperature in Kelvin
  ln = log(RT / RT0);
  TX = 1 / ((ln / B) + (1 / T0));

  // Convert to Celsius
  float tempC = TX - 273.15;
  float tempK = TX;
  float tempF = (tempC * 1.8) + 32;

  // Serial monitor output
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.print("C\t");
  Serial.print(tempK);
  Serial.print("K\t");
  Serial.print(tempF);
  Serial.println("F");

  // LCD Display
  lcd.clear();
  if (isnan(tempK) || isnan(tempC)) {
    lcd.setCursor(0, 0);
    lcd.print("Read Failed");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("TempC: ");
    lcd.print(tempC, 1); // One decimal point
    lcd.print((char)223);
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("TempK: ");
    lcd.print(tempK, 1);
    lcd.print("K");
  }

  delay(1000); // 1 second delay
}
