#include<stdlib.h>

// Oled
#include <Wire.h>
#include <SeeedOLED.h>

//Light Sensor
#define LIGHTSENSORPIN 0

//Solid Moisture Sensor
#define SOLIDMOISTUREPIN 2

//DHT11
#include "DHT.h"
#define DHTPIN 4     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

//RELAY
#define LEDPIN 13
#define RELAYPIN 7

void setup()
{
  //Uart
  Serial.begin(115200); // open serial connection to USB Serial port (connected to your computer)
  Serial1.begin(57600); // open internal serial connection to MT7688
  // in MT7688, this maps to device

  //RELAY LED
  pinMode(LEDPIN, OUTPUT);
  pinMode(RELAYPIN, INPUT);

  // OLED DISPLAY
  Wire.begin();
  SeeedOled.init();  //initialze SEEED OLED display
  DDRB |= 0x21;
  PORTB |= 0x21;

  SeeedOled.clearDisplay();          //clear the screen and set start position to top left corner
  SeeedOled.setNormalDisplay();      //Set display to normal mode (i.e non-inverse mode)
  SeeedOled.setPageMode();           //Set addressing mode to Page Mode
  SeeedOled.setTextXY(0, 0);         //Set the cursor to Xth Page, Yth Column
  SeeedOled.putString("-SENSOR STATUS-"); //Print the String

  //Humid / Temper
  dht.begin();
}

void loop()
{
#if 1
  //Light Sensor
  int _lightsensor = analogRead(LIGHTSENSORPIN);
  String s =  "L:";
  s += String(_lightsensor);
  Serial1.println(s); s="";
  SeeedOled.setTextXY(3, 0);          //Set the cursor to 2nd Page, 0th Column
  SeeedOled.putString("1. Light:"); //Print the String
  SeeedOled.putNumber(_lightsensor);        //Print number

  //Solid Moisture Sensor
  int _solidsensor = analogRead(SOLIDMOISTUREPIN);
  s +=  "M:";
  s += String(_solidsensor);
  Serial1.println(s); s="";
  SeeedOled.setTextXY(4, 0);          //Set the cursor to 2nd Page, 0th Column
  SeeedOled.putString("2. Moist:"); //Print the String
  SeeedOled.putNumber(_solidsensor);        //Print number

  //Temper
  int _temperature = dht.readTemperature();             /* read the temperature value from the sensor */
  if (isnan(_temperature) || _temperature < 1 || _temperature > 50)
  {
    _temperature = -1;
  }
  else
  {
    s +=  "T:";
    s += String(_temperature);
    Serial1.println(s); s="";
    SeeedOled.setTextXY(5, 0);          //Set the cursor to 2nd Page, 0th Column
    SeeedOled.putString("3. Tempe:"); //Print the String
    SeeedOled.putNumber(_temperature);        //Print number
  }

  //Humid
  int _humidity = dht.readHumidity();                   /* read the humidity value from the sensor */
  if (isnan(_humidity) || _humidity < 0 || _humidity > 100)
  {
    _humidity = -1;
  }
  else
  {
    s +=  "H:";
    s += String(_humidity);
    Serial1.println(s); s="";
    SeeedOled.setTextXY(6, 0);          //Set the cursor to 2nd Page, 0th Column
    SeeedOled.putString("4. Humid:"); //Print the String
    SeeedOled.putNumber(_humidity);        //Print number
}


  //RELAY:GPIO4, LED: GPIO13
#if 0
  if (Serial1.available() > 0)
  {
    int iCnt = 0;
    int chr = -1;
    String sSerial = "";
    while ((chr = Serial1.read()) != -1)
    {
      sSerial += (char)chr;
      iCnt++;
    }
    SeeedOled.setTextXY(2, 0);          //Set the cursor to 1st Page, 0th Column
    SeeedOled.putString("0. Relay:"); //Print the String
    if (sSerial.equals("Relay|1"))
    {
      digitalWrite(LEDPIN, 1);
      digitalWrite(RELAYPIN, 1);
      SeeedOled.putNumber(1);
    }
    else if (sSerial.equals("Relay|0"))
    {
      digitalWrite(LEDPIN, 0);
      digitalWrite(RELAYPIN, 0);
      SeeedOled.putNumber(0);
    }
    else
    {
      SeeedOled.putNumber(iCnt);
    }
  }
#else
  int _relay = digitalRead(RELAYPIN);
  SeeedOled.setTextXY(2, 0);          //Set the cursor to 1st Page, 0th Column
  SeeedOled.putString("0. Relay:"); //Print the String
  SeeedOled.putNumber(_relay);
#endif


  // UART WRITE
  #if 0
  //if(++iUartCnt > 10)
  {
    iUartCnt = 0;
    Serial1.println(s);
  }
  #endif
  
  delay(2000);
#endif
}

