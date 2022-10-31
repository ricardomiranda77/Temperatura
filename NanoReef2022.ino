// Controle de Temperatura ESP8266 novo Blynk
// 13/06/2022
// Temperatura minima 24.5C <> 25.0C
// Temperatura maxima 27.0C <> 26.5C

#define BLYNK_TEMPLATE_ID ""
#define BLYNK_DEVICE_NAME ""
#define BLYNK_AUTH_TOKEN ""

#define BLYNK_PRINT Serial

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial
#define ONE_WIRE_BUS 13 // D7

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <OneWire.h>
#include <DallasTemperature.h> 

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);

int Ventilador = 16 ; // D0  porta que esta ligado o Ventilador
int Aquecedor = 14 ; // D5  porta que esta ligado o Aquecedor
int lederro = 1 ;  // TX 
float temp;
WidgetLED led1(V2);
WidgetLED led2(V3);
WidgetLED led3(V4);

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";

  
BlynkTimer timer;


void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  DS18B20.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);

  pinMode(lederro, OUTPUT);
  pinMode(Aquecedor, OUTPUT); 
  pinMode(Ventilador, OUTPUT);
  digitalWrite(Ventilador,LOW);
  digitalWrite(Aquecedor,LOW);
  
}

void loop()
{
  Blynk.run();
  timer.run();
  termostato();
}

/***********************************************/

void sendSensor()
{
  DS18B20.requestTemperatures(); 
  float t = DS18B20.getTempCByIndex(0);
  temp = t;

  // You can send any value at any time.
  // Please don't send more that 10 values per second.
    Blynk.virtualWrite(V0, t);
}


void termostato()
{
   if (temp > 0 && temp < 50){
    
  led3.off();
 if ( temp > 27.00 ) {
    digitalWrite(Ventilador,HIGH);
    led2.on();
 } 
  if ( temp < 26.50 ){
    digitalWrite(Ventilador,LOW);
    led2.off();
    
  }
  
  if ( temp < 24.40 ) {
    digitalWrite(Aquecedor,HIGH);
    led1.on();
  }
    if ( temp > 24.90 ) {
      digitalWrite(Aquecedor,LOW);
      led1.off();
      
    }
     }else
     {
      
      led3.on();
      digitalWrite(Ventilador,LOW);
      led2.off();
      digitalWrite(Aquecedor,LOW);
      led1.off();
      delay(500);
      digitalWrite(lederro,LOW);
      delay(500);
      digitalWrite(lederro,HIGH);
      
     }
}
