#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Time Libraries
#include <Wire.h>
#include <RTClib.h>

DS3231 rtc;

bool checkShowBullets = false;

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10

// Hardware SPI connection
MD_Parola Matrix = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
uint8_t scrollSpeed = 25;    // default frame delay value
textEffect_t scrollEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_LEFT;
uint16_t scrollPause = 1000; // in milliseconds

char messageToDisplay[75] = "Sofronas";

void setup(void)
{
  Serial.begin(9600);
  
  while (!Serial) ; // wait for serial
  delay(200);
#ifdef AVR
  Wire.begin();
#else
  Wire1.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
#endif
  rtc.begin();

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }
  Matrix.begin();
  Matrix.setIntensity(0);
  Matrix.displayText("sofron", PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
}

void loop(void)
{
  String showTime = "";
  DateTime now1 = rtc.now();
  int h = now1.hour();
  int m = now1.minute();
  String hourString = ((h >= 10) ? String(h) : "0" + String(h));
  String minString = ((m >= 10) ? String(m) : "0" + String(m));
  if(checkShowBullets == false)
  {
    showTime = hourString + ":" + minString;
    checkShowBullets = true;
  } else {
    showTime = hourString + " " + minString;
    checkShowBullets = false;
  }
  Matrix.print(showTime);
//  delay(1000);
  delay(500);
}
