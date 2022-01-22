#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_Sensor.h>
#include "UTFT.h"
//DEFINES
#define DHTPIN 8     // Digital pin connected to the DHT sensor 
#define DHTTYPE DHT22     // DHT 11

//VARIABLES
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

// Declare which fonts we will be using
extern uint8_t GroteskBold32x64[];

// Set the pins to the correct ones for your development shield
// ------------------------------------------------------------
// Arduino Uno / 2009:
// -------------------
// Standard Arduino Uno/2009 shield            : <display model>,A5,A4,A3,A2
// DisplayModule Arduino Uno TFT shield        : <display model>,A5,A4,A3,A2
//
// Arduino Mega:
// -------------------
// Standard Arduino Mega/Due shield            : <display model>,38,39,40,41
// CTE TFT LCD/SD Shield for Arduino Mega      : <display model>,38,39,40,41
//
// Remember to change the model parameter to suit your display module!
UTFT myGLCD(ILI9486, 38, 39, 40, 41);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  delayMS = 1000;

  // Setup the LCD
  myGLCD.InitLCD();
  myGLCD.setFont(GroteskBold32x64);
  myGLCD.fillScr(0, 0, 0);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 0, 0);
}

void loop() {
//put your main code here, to run repeatedly:
// Clear the screen and draw the frame
  //myGLCD.clrScr();

  //Delay between measurements.
  delay(delayMS);

  //Get temperature event and print its value.
  sensors_event_t event;

  dht.temperature().getEvent(&event);

  if (!isnan(event.temperature)) 
  {
    myGLCD.print("TEMP (F): " + String(round(((event.temperature * 9) / 5) + 32)) + "F", LEFT, 1);
    myGLCD.print("TEMP (C): " + String(round(event.temperature)) + "C", LEFT, 130); 
  }

  //Get humidity event and print its value.
  dht.humidity().getEvent(&event);

  if (!isnan(event.relative_humidity)) 
  {
    myGLCD.print("HUMIDITY: " + String(round(event.relative_humidity)) + "%", LEFT, 260);
  }
}