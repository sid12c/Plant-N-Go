#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
#define DELAY 500 // Delay between two measurements in ms
#define VIN 5 // V power voltage
#define R 10000 //ohm resistance value
#define PIN_A   5
#define PIN_B   6

// Parameters
const int sensorPin = A0; // Pin connected to sensor

//Variables
int sensorVal; // Analog value from the sensor
int lux; //Lux value

LiquidCrystal_I2C lcd(0x27, 20, 4);  // I2C address 0x3F, 16 column and 2 rows
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  dht.begin();     // initialize the sensor
  lcd.init();      // initialize the lcd
  lcd.backlight(); // open the backlight
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(8, OUTPUT);  
}

void loop()
{
 
  sensorVal = analogRead(sensorPin);
  lux= (sensorVal*5.86977)-17.8642;
  Serial.print('l');
  Serial.println(lux);

  delay(2000); // wait a few seconds between measurements

  float humi  = dht.readHumidity();    // read humidity
  float tempC = dht.readTemperature(); // read temperature

  lcd.clear();
  // check if any reads failed
  if (isnan(humi) || isnan(tempC)) {
    lcd.setCursor(0, 0);
    lcd.print("Failed");
  } else {
    lcd.setCursor(0, 0);  // start to print at the first row
    lcd.print("Temp: ");
    lcd.print(tempC);     // print the temperature
    lcd.print((char)223); // print ° character
    lcd.print("C");
    Serial.print('C');
    Serial.println(tempC);

    lcd.setCursor(0, 1);  // start to print at the second row
    lcd.print("Humi: ");
    lcd.print(humi);      // print the humidity
    lcd.print("%");
    Serial.print('H');
    Serial.println(humi);
   
    if (humi < 50.0) {
      digitalWrite(PIN_A,LOW);
      digitalWrite(PIN_B,HIGH);
    } else {
      digitalWrite(PIN_A,LOW);
      digitalWrite(PIN_B,LOW);
    }

  }
 
  delay(2000);  
  lcd.clear();
  lcd.setCursor(0, 0);  // start to print at the first row
  lcd.print("Light: ");
  lcd.print(lux);     // print the temperature
  lcd.print(" Lux");  
  if (lux < 300){
    digitalWrite(8, HIGH);
  }
  else {
  digitalWrite(8, LOW);    
  }
}
int sensorRawToPhys(int raw){
  // Conversion rule
  float Vout = float(raw) * (VIN / float(1023));// Conversion analog to voltage
  float RLDR = (R * (VIN - Vout))/Vout; // Conversion voltage to resistance
  int phys=500/(RLDR/1000); // Conversion resitance to lumen
}