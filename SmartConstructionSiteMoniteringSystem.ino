#include "dht.h"
#define dht_apin A2 // Analog Pin sensor is connected to
#include <SoftwareSerial.h>
dht DHT;
const int sensorPin = A1;  // Define the analog pin connected to the sound sensor
int mq=A0;
int x;
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
SoftwareSerial espSerial(5, 6);
String str;
void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);
  pinMode(A0,INPUT);//Wait before accessing Sensor// Initialize serial communication at 9600 baud rate
   //lcd.begin();
   lcd.init();
   lcd.backlight();
}
void loop() {
  int sensorValue = analogRead(sensorPin);  // Read the analog value from the sensor
  // Approximate dB conversion (reference voltage assumed as 5V)
  float voltage = sensorValue * 5.0 / 1023.0;  // Convert sensor value to voltage (0-5V)
  float dB = 20 * log10(voltage / 0.0002)-25;
  Serial.print("Sound Level (dB): ");
  Serial.println(dB);
  DHT.read11(dht_apin);
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    x=analogRead(A0);
    Serial.print("MQ-6 output: ");
    Serial.println(x);

    lcd.setCursor(0,0);
    lcd.print("H=");
    lcd.print(DHT.humidity);
    lcd.print("%");
    lcd.setCursor(8,0);
    lcd.print("T=");
    lcd.print(DHT.temperature); 
    lcd.print("C");
    lcd.setCursor(0,1);
    x=analogRead(A0);
    lcd.print("G:");
    lcd.print(x);
    lcd.setCursor(8,1);
    lcd.print("S=");
    lcd.print(dB);
    str =String("coming from arduino: ")+String("H= ")+String(h)+String("T= ")+String(t);
    espSerial.println(str);
    delay(1000);
}
