//CONFIGURACION DE MI HORA ... CON RTC DE BLYNKKKK
#include <ESP8266WiFi.h>  //bibloteca de wifi
#include <ESP8266WiFi.h>      //incluyo libreria de wifi del micro
#include <BlynkSimpleEsp8266.h>  //bibloteca de app blynk 
#include <SPI.h>
#include <TimeLib.h>   //libreria de rtc real time
#include <WidgetRTC.h>
/////////////////////////////////////////////////////////////////////////////////////////////////
//Uso para el DHT22  TEMPERATURA Y HUMEDAD!!!!!
#include "DHT.h" 

 //OBJETO INTERIOR
const int DHTPinINTERIOR = 05;     // UTILIZO EL (PIN 1) DEL ESP8266 PARA MI PRIMER DHT interior

const int DHTPinEXTERIOR = 00;     // UTILIZO EL (PIN 8) DEL ESP8266 PARA MI PRIMER DHT interior

DHT dhtINTERIOR(DHTPinINTERIOR, DHT22);    //DEFINI EL PRIMER OBJEETO DE TEMPERATURA EL DCHT22 ES MI SENSOR DE TEMP TAMBIEN PUEDE SER EL DHT11

DHT dhtEXTERIOR(DHTPinEXTERIOR, DHT22);    //DEFINI EL PRIMER OBJEETO DE TEMPERATURA EL DCHT22 ES MI SENSOR DE TEMP TAMBIEN PUEDE SER EL DHT11


void setup() {
  
 //CONTINUACION DEL DHT22 TEMPERATURA Y HUMEDAD
   Serial.begin(9600);


  //INICIA EL SENSOR DE TEMP
   dhtINTERIOR.begin();
   
   dhtEXTERIOR.begin();


}

void loop() {
  //LAMADAS A MI FUNCIONES !!!
  TempINTERIOR ();
  TempEXTERIOR ();
  
   delay(4000);

   //IMPRIMO EN BLYNK
      
   }

  void TempINTERIOR (){

    // Lee temperatura y humedad durante unos 250ms
   float t = dhtINTERIOR.readTemperature();
   float h = dhtINTERIOR.readHumidity();

  int TEMPERATURAinterior = t*100;
  int HUMEDADinterior = h*100;

  if (isnan(t) || isnan(h)) 
   {
      Serial.println(" \t Fallo en la lectura \t");
      
       delay(500);
      return;
   }
   
   Serial.print("Temperatura Interior: ");
   Serial.print(t);
   Serial.print(" *C ");
   Serial.print(" %\t");
   Serial.print("Humedad relativa: ");
   Serial.print(h);
   Serial.print(" %\n");
    }

    
  void TempEXTERIOR (){

    // Lee temperatura y humedad 
   float t = dhtEXTERIOR.readTemperature();
   float h = dhtEXTERIOR.readHumidity();

  int TEMPERATURAinterior = t*100;
  int HUMEDADinterior = h*100;

  if (isnan(t) || isnan(h)) 
   {
      Serial.println(" \t Fallo en la lectura \t");
      
       delay(500);
      return;
   }
   
   Serial.print("Temperatura EXTERIOR: ");
   Serial.print(t);
   Serial.print(" *C ");
   Serial.print(" %\t");
   Serial.print("Humedad relativa EXTERIOR: ");
   Serial.print(h);
   Serial.print(" %\n");
    }
