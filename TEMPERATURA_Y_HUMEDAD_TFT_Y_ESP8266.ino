
/////////////////////////////////////////////////////////////////////////////////////////////////

//CONFIGURACION DE MI HORA ... CON RTC DE BLYNKKKK
#include <ESP8266WiFi.h>  //bibloteca de wifi

#include <BlynkSimpleEsp8266.h>  //bibloteca de app blynk 
#include <SPI.h>
#include <TimeLib.h>   //libreria de rtc real time
#include <WidgetRTC.h>

//declaro lo que puse en blynk 

WidgetLCD lcdHora(V2);    //DISPLAYS DE BLINK
WidgetLCD lcd(V0);
WidgetLCD lcd2(V5);

BlynkTimer timer; //Estas dos son para el reloj de tiempo real
WidgetRTC rtc;   //    Widget RTC (no requiere pin)

 int dia = day();
 int minuto= minute();

  int segundos;

// se pone el token que me envio al mail la app
char auth[] = "3e186b4f96a04add95830f473e9dbc63";


//WIFI  y contraseña 

char ssid[] = "CasaFlorida";
char pass[] = "95187249P#1";



//LLAMADA A LA INICIACION DE MI RELOJ DE TIEMPO REAL!!!!!!!!!!!!!!!!!!!!!!!!

BLYNK_CONNECTED() {         //saber comooooo funcionaaaaaaa
  // Sincronizo con el real time para la hora exacta del momento
  rtc.begin();
}


/////////////////////////////////////////////////////////////////////////////////////////////////

#include <Adafruit_GFX.h>    // Include core graphics library
#include <Adafruit_ILI9341.h> // Include Adafruit_ILI9341 library to drive the display


// Declare pins for the display:
#define TFT_DC 4              
#define TFT_CS 2              
#define TFT_RST 0    

// The rest of the pins are pre-selected as the default hardware SPI for Arduino Uno (SCK = 13 and SDA = 11)

// Create display:
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_DC, TFT_CS, TFT_RST);

#include <Fonts/FreeSerif24pt7b.h>  // Add a custom font


/////////////////////////////////////////////////////////////////////////////////////////////////
//Uso para el DHT22  TEMPERATURA Y HUMEDAD!!!!!
#include "DHT.h" 

 //OBJETO INTERIOR
const int DHTPinINTERIOR = 15;     //gpio 15,,, UTILIZO EL (PIN 8)!! DEL ESP8266 PARA MI PRIMER DHT interior

DHT dhtINTERIOR(DHTPinINTERIOR, DHT22);    //DEFINI EL PRIMER OBJEETO DE TEMPERATURA EL DCHT22 ES MI SENSOR DE TEMP TAMBIEN PUEDE SER EL DHT11

  //OBJETO EXTERIOR
  const int DHTPinEXTERIOR = 12;     //gpio12,,, UTILIZO EL (PIN 3)!! DEL ESP8266 PARA MI PRIMER DHT exterior

DHT dhtEXTERIOR(DHTPinEXTERIOR, DHT22);    //DEFINI EL SEGUNDO OBJEETO DE TEMPERATURA EL DCHT22 ES MI SENSOR DE TEMP TAMBIEN PUEDE SER EL DHT11


///////////////////////////////////////////////////////////////////////////////////////
//LIBRERIA DEL SENSOR PRESION
#include <Wire.h>
#include <Adafruit_BMP085.h>

// BMP180  voltaje de 3,3V a 5V es el remplazo del BMP085
// BMP085  voltaje 3,3V

Adafruit_BMP085 MySensorBMP;  //CREO EL OBJETO !!!

////////////////////////////////////////////////////////////////////////////////////////////////////////
  
void setup() {

    lcdHora.clear(); //lo uso para borrar el LCD Widget
  

 Blynk.begin(auth, ssid, pass);

//CONFIGURACION DE VALORES DE INICIO DE MI DISPLAY!!!

// Display setup:  IMPRIMO LO QUE QUIERO EN MI PANTALLA 
  
  tft.begin();  // Initialize display

  tft.fillScreen(0x0000);  // Fill screen with black

  tft.setRotation(180);  // Set orientation of the display. Values are from 0 to 3. If not declared, orientation would be 0,
                         // which is portrait mode.

  tft.setTextWrap(false);  // By default, long lines of text are set to automatically “wrap” back to the leftmost column.
                           // To override this behavior (so text will run off the right side of the display - useful for
                           // scrolling marquee effects), use setTextWrap(false). The normal wrapping behavior is restored
                           // with setTextWrap(true).



  // We are going to print on the display everything that is static on the setup, to leave the loop free for dynamic elements:

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw rounded rectangle:
  tft.drawRoundRect(1, 80, 239, 239, 10, 0xBBBE);  // Draw rounded rectangle (x,y,width,height,radius,color)
                                                       // It draws from the location to down-right
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Write to the display the text "Hello":
  tft.setCursor(25, 85);  // Set position (x,y)
  tft.setTextColor(0xF815);  // Set color of text. First is the color of text and after is color of background
  tft.setTextSize(3.9999999999999988888899);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
  tft.println("TEMPERATURA");  // Print a text or value
/*
  tft.setCursor(110,135);  // Set position (x,y)
  tft.setTextColor(0xF5B7);  // Set color of text. We are using custom font so there is no background color supported
  tft.setTextSize(4);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
  tft.println("C");  // Print a text or value

  tft.setCursor(218,135);  // Set position (x,y)
  tft.println("C");  // Print a text or value
*/

  tft.setCursor(25, 180);  // Set position (x,y)
  tft.setTextColor(0xFEEB);  // Set color of text. First is the color of text and after is color of background
  tft.setTextSize(2.9999999);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
  tft.println("INDOOR");  // Print a text or value

  
  tft.setCursor(145, 180);  // Set position (x,y)
  tft.setTextColor(0xCEDA);  // Set color of text. First is the color of text and after is color of background
  tft.setTextSize(2.9999999);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
  tft.println("OUTSIDE");  // Print a text or value


  /////////////////////////////////////////////////////////////////////////////////////////
    // Draw line:
  tft.drawLine(0, 198, 240, 198, 0xD7DF);  // Draw line (x0,y0,x1,y1,color)
  
  tft.drawLine(123, 110, 123, 200, 0xFAEA);  // Draw line (x0,y0,x1,y1,color)


  /////////////////////////////////////////////////////////////////////////////////////////

  
  tft.setCursor(60, 205);  // Set position (x,y)
  tft.setTextColor(0xAFFA);  // Set color of text. First is the color of text and after is color of background
  tft.setTextSize(2.99999999999999999);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
  tft.println("HUMEDAD");  // Print a text or value

  tft.setCursor(25, 270);  // Set position (x,y)
  tft.setTextColor(0xFEEB);  // Set color of text. First is the color of text and after is color of background
  tft.setTextSize(2.9999999);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
  tft.println("INDOOR");  // Print a text or value

  
  tft.setCursor(130, 270);  // Set position (x,y)
  tft.setTextColor(0xCEDA);  // Set color of text. First is the color of text and after is color of background
  tft.setTextSize(2.9999999);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
  tft.println("OUTSIDE");  // Print a text or value


  tft.setCursor(110,106);  // Set position (x,y)
  tft.setTextColor(0xFFF6);  // Set color of text. We are using custom font so there is no background color supported
  tft.setTextSize(2);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
  tft.println("o");  // Print a text or value

  tft.setCursor(225,106);  // Set position (x,y)
  tft.println("o");  // Print a text or value


  tft.setCursor(103,239);  // Set position (x,y)
  tft.setTextColor(0xFFF6);  // Set color of text. We are using custom font so there is no background color supported
  tft.setTextSize(3);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
  tft.println("%");  // Print a text or value

  tft.setCursor(217,239);  // Set position (x,y)
  tft.println("%");  // Print a text or value

  
  /////////////////////////////////////////////////////////////////////////////////////////

  tft.drawLine(0, 285, 240, 285,0xEC86);  // Draw line (x0,y0,x1,y1,color)

 
  /////////////////////////////////////////////////////////////////////////////////////////

  tft.setCursor(5, 288);  // Set position (x,y)
  tft.setTextColor(0xAFB3);  // Set color of text. First is the color of text and after is color of background
  tft.setTextSize(2);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
  tft.println("PRESION");  // Print a text or value
  
  tft.setCursor(8, 303);  // Set position (x,y)
  tft.println("ATM");  // Print a text or value
  
  tft.setCursor(45, 305);  // Set position (x,y)
  tft.setTextColor(0xCEDA);  // Set color of text. First is the color of text and after is color of background
  tft.setTextSize(1.9);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
  tft.println("OUTSIDE");  // Print a text or value

  tft.setCursor(215, 295);  // Set position (x,y)
  tft.setTextColor(0xAFB3);  // Set color of text. First is the color of text and after is color of background
  tft.setTextSize(1.5);
  tft.println("hPa");  // Print a text or value

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
  tft.setCursor(68,150);  // Set position (x,y)
  tft.setTextColor(0xFF44);  // Set color of text. First is the color of text and after is color of background
  tft.setTextSize(3);
  tft.println(".");
  
  tft.setTextSize(3);
  tft.setCursor(59,247);  // Set position (x,y)
  tft.println(".");

  tft.setCursor(183,150);  // Set position (x,y)
  tft.setTextColor(0xFF44);  // Set color of text. First is the color of text and after is color of background
  tft.setTextSize(3);
  tft.println(".");
  
  tft.setTextSize(3);
  tft.setCursor(176,247);  // Set position (x,y)
  tft.println(".");

  // Stop using a custom font
  tft.setFont();  // Reset to standard font, to stop using any custom font previously set

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //CONTINUACION DEL DHT22 TEMPERATURA Y HUMEDAD
   Serial.begin(9600);

  //INICIA EL SENSOR DE TEMP
   dhtINTERIOR.begin();
   dhtEXTERIOR.begin();

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//INICIO DEL SENSOR DE PRESION

  // MySensorBMP.begin();
   

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//IMPRIMO EN LA APP DE BLINK

  lcdHora.clear();
  lcd.clear(); //lo uso para borrar el LCD Widget
  lcd2.clear(); //lo uso para borrar el LCD Widget
  

  lcdHora.print(4,0, ":");
  
  
  lcd.print(0,0,"TEMP INT:");
  lcd.print (0,1,"HUMEDAD INT:");

  lcd2.print(0,0,"TEMP EXT:");
  lcd2.print(0,1,"HUMEDAD EXT:");

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7  
void loop() {

//HORAAAAAAAAAAAAAAAAAAAA

  timer.run();
  
  Blynk.run();     //finalmente se corre constantemente en blynk porque estoy en loop (ciclo infinito)
  
  lcdHora.print(4,0, ":");
  
  
  lcd.print(0,0,"TEMP INT:");
  lcd.print (0,1,"HUMEDAD INT:");

  lcd2.print(0,0,"TEMP EXT:");
  lcd2.print(0,1,"HUMEDAD EXT:");

//LLAMADA A MIS FUNCIONES PARA IMPRESION DINAMICA EN EL LOOP


  clockDisplay(); // llamo a la funion para mostrar la hora! 



// IMPRIMO TEMP Y HUMEDAD EN EL LOOP 
  TemperaturaHumedadINTERIOR();
  
  TemperaturaHumedadEXTERIOR();

  PRESION();
 

   delay(300);  //delay de 1 seg
}

//FUNCION DE LA HORA QUE LA LEVANTO DE BLYNK CON EL RTC DEL MISMO MEDIANTE WIFI TODO!!!!!!!!!!!! POR LO TANTO NO TUVE QUE COMPRAR UN RELOJ DE TIEMPO REAL!!!!!!!!!!!!!!!!

void clockDisplay()
   {

  // Llamo a la hora (), minuto (), ... en cualquier momento

  String currentTime = String(hour()) +":" + minute() ;
  String currentDate = String(day()) + " - " + month() + " - " + year();

 // imprimo en la App DE BLYNK EN EL LCD

  lcdHora.print(0,0, currentTime);
  lcdHora.print(5,0, second()); 
  lcdHora.print(0,0, currentTime);  
 
  // Send date to the App
  lcdHora.print(0,1, currentDate);
  
  
  //IMPRIMO EN EL SERIAL 
  
  Serial.print("HORA\t");
  Serial.print(currentTime +"\t");
  // Send date to the App
  Serial.print(currentDate);

  //IMPRIMO EN EL TFT QUE ES LO QUE ME INTEREZA !!!!!!!!!

  // Display setup:  IMPRIMO LO QUE QUIERO EN MI PANTALLA
  
//HORA
     
  // There is a problem when we go, for example, from 100 to 99 because it doesn't automatically write a background on
  // the last digit we are not longer refreshing. We need to check how many digits are and fill the space remaining.

  //EVITANDO ERRORES DE MUESTREO EN TFT 
  
  if(second() < 10)  // TENGO QUE HACER NEGRA LA PARTE ESA PORQUE SINO VEO ALGO QUE NO QUIERO EN MI DISPLAY
  {
    // Fill the other digit with background color:
     tft.fillRect(215, 5, 24, 30, 0x0000);  // Draw filled rectangle (x,y,width,height,color)
     
     tft.setCursor(200, 5);  // Set position (x,y)
     tft.setTextColor(0xCFF5, 0x0000);  // Set color of text. First is the color of text and after is color of background
     tft.setTextSize(3);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
     tft.println(second());  // Print a text or value
         
  }
  else 
  {
    tft.setCursor(200, 5);  // Set position (x,y)
    tft.setTextColor(0xCFF5, 0x0000);  // Set color of text. First is the color of text and after is color of background
    tft.setTextSize(3);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
    tft.println(second());  // Print a text or value
  }
  
  if(minute() < 10 )  // If Variable1 is less than 10...   
  {
    // Fill the other digit with background color:
     tft.fillRect(160, 5, 35 , 50, 0x0000);  // Draw filled rectangle (x,y,width,height,color)
     
     tft.setCursor(20, 5);  // Set position (x,y)
     tft.setTextColor(0xF7D6, 0x0000);  // Set color of text. First is the color of text and after is color of background
     tft.setTextSize(6);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
     tft.println(currentTime);  // Print a text or value

  }
  else
  {
      // Write to the display the Variable1 with left text alignment:
  tft.setCursor(20, 5);  // Set position (x,y)
  tft.setTextColor(0xF7D6, 0x0000);  // Set color of text. First is the color of text and after is color of background
  tft.setTextSize(6);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
  tft.println(currentTime);  // Print a text or value
  }

    if(hour() < 10)  // If Variable1 is less than 10...
  {
    // Fill the other digit with background color:
     tft.fillRect(160, 5, 35 , 50, 0x0000);  // Draw filled rectangle (x,y,width,height,color)

     tft.setCursor(20, 5);  // Set position (x,y)
     tft.setTextColor(0xF7D6, 0x0000);  // Set color of text. First is the color of text and after is color of background
     tft.setTextSize(6);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
     tft.println(currentTime);  // Print a text or value         
  }

  else
  {
      // Write to the display the Variable1 with left text alignment:
  tft.setCursor(20, 5);  // Set position (x,y)
  tft.setTextColor(0xF7D6, 0x0000);  // Set color of text. First is the color of text and after is color of background
  tft.setTextSize(6);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
  tft.println(currentTime);  // Print a text or value
  
  }

//DIA
  tft.setCursor(15, 55);  // Set position (x,y)
  tft.setTextColor(0xFB5E,0x0000);  // Set color of text. First is the color of text and after is color of background
  tft.setTextSize(3.9);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
  tft.println(currentDate);  // Print a text or value


}

//ESTE ES EL SENOR INTERIOR DHT22
///////////////////////////////////////////////////////////////////////////////////////////////
void TemperaturaHumedadINTERIOR()
{

  
  // Lee temperatura y humedad durante unos 250ms
   float t =dhtINTERIOR.readTemperature();
   float h =dhtINTERIOR.readHumidity();

//SI FALLA LA LECTURA ENTONCES NO SEGUIRE!!!

   if (isnan(t) || isnan(h)) 
   {
      Serial.println(" \t Fallo en la lectura \t");
      return;
   }   
  
  int TempInt=t;
  int HumedadInt=h;
  
  int TEMPERATURAinterior = t*100;
  int HUMEDADinterior = h*100;

  //CADA VEZ QUE SE LLAMA EN PRIMERA INSTANCIA BORRO LO VIEJO !!!
  //CORRECCION PARA EL NO PARPADEO DEL DISPLAY DE LA TEMP Y HUMEDAD 

    //BORRO TEMP INT
     tft.fillRect(3, 125, 71 , 45, 0x0000);  // Draw filled rectangle (x,y,width,height,color)
     tft.fillRect(79, 125, 39 , 45, 0x0000);  // Draw filled rectangle (x,y,width,height,color)
     
    //BORRO HUMEDAD INT
     tft.fillRect(3, 232, 60 , 36, 0x0000);
     tft.fillRect(70, 232, 30 , 36, 0x0000);

 
 //CORRECCION DE UBICACION DE NUMEROS DE TEMP Y HUMEDAD VALORES
//valores menores borro display en tal posicion..  
   if (t<10)
  { 
    tft.fillRect(3, 125, 40, 45, 0x0000);  // Draw filled rectangle (x,y,width,height,color)
    tft.setTextSize(6);  // Set text size. We are using custom font so you should always set text size as 0   
    tft.setCursor(44, 125);  // Set position (x,y)
    tft.setTextColor(0xFEF6);  // Set color of text. We are using custom font so there is no background color supported
    tft.println((TEMPERATURAinterior/100));  // IMPRIMO EL ENTERO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    
    tft.setTextSize(6);
    tft.setCursor(83, 125);  // Set position (x,y)
    tft.setTextColor(0xFEF6);  // Set color of text. We are using custom font so there is no background color supported
    tft.println(((TEMPERATURAinterior/100)-TempInt)*10 , 0);  // IMPRIMO EL VALOR DECIMAL DESPUES DE LA COMA !!!!!!  EL 2 INDICA QUE PONGO 0 DECIMALESSS
  }
  
  else {
    tft.setTextSize(6);  // Set text size. We are using custom font so you should always set text size as 0   
    tft.setCursor(8, 125);  // Set position (x,y)
    tft.setTextColor(0xFEF6);  // Set color of text. We are using custom font so there is no background color supported
    tft.println((TEMPERATURAinterior/100));  // IMPRIMO EL ENTERO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  
    tft.setTextSize(6);
    tft.setCursor(83, 125);  // Set position (x,y)
    tft.setTextColor(0xFEF6);  // Set color of text. We are using custom font so there is no background color supported
    tft.println(((TEMPERATURAinterior*0.01)-int(TempInt))*10 , 0);  // IMPRIMO EL VALOR DECIMAL DESPUES DE LA COMA !!!!!!   POR EJ TENGO 2345--> PENSARLO OBTENGO EL 4.5!!
  }
//------------------------------------------------------------------------------------------------------------------------------------------

    if(h<10)
  {
     tft.fillRect(3, 232, 27, 36, 0x0000);  // Draw filled rectangle (x,y,width,height,color)
     tft.setTextSize(5);  // Set text size. We are using custom font so you should always set text size as 0   
     tft.setCursor(31, 232);  // Set position (x,y)
     tft.setTextColor(0xCFFE);  // Set color of text. We are using custom font so there is no background color supported
     tft.println(HUMEDADinterior/100);  // Print a text or value

    tft.setTextSize(5);
    tft.setCursor(75, 232);  // Set position (x,y)
    tft.setTextColor(0xCFFE);  // Set color of text. We are using custom font so there is no background color supported
    tft.println(((HUMEDADinterior*0.01)-HumedadInt)*10 ,0);  // IMPRIMO EL VALOR DECIMAL DESPUES DE LA COMA !!!!!!
  }
  else 
  {
  tft.setTextSize(5);  // Set text size. We are using custom font so you should always set text size as 0   
  tft.setCursor(7, 232);  // Set position (x,y)
  tft.setTextColor(0xCFFE);  // Set color of text. We are using custom font so there is no background color supported
  tft.println(HUMEDADinterior/100);  // Print a text or value

  tft.setTextSize(5);
  tft.setCursor(75, 232);  // Set position (x,y)
  tft.setTextColor(0xCFFE);  // Set color of text. We are using custom font so there is no background color supported
  tft.println(((HUMEDADinterior*0.01)-HumedadInt)*10,0);  // IMPRIMO EL VALOR DECIMAL DESPUES DE LA COMA !!!!!!*/
  }
  
 
  
   Serial.print("Temperatura Interior: ");
   Serial.print(TEMPERATURAinterior);
   Serial.print(" *C ");
   Serial.print(" %\t");
   Serial.print("Humedad relativa: ");
   Serial.print(HUMEDADinterior);
   Serial.print(" %\n");

   //IMPRIMO EN BLYNK

   lcd.print(9,0,t);
   lcd.print(12,1,h);

   
//RANGOS DE HUMEDAD Y TEMP DE MI INTERES
   //https://actitudecologica.com/temperatura-de-confort-cual-es-temperatura-ideal-casa/

//JUEGO CON LOS VALORES LIMITES !!!
if ( h < 40 )
{
  Blynk.email("mateomenvielle@hotmail.com", "HUMEDAD INTERIOR  < 40%)!!! ", "LA HUMEDAD  ES MENOR A 40(ESO NO ES BUENO --> Por debajo de estos valores empiezan a aparecer bacterias,virus y afecciones respiratorias");
} 

else if ( h > 60) 
 {
   Blynk.email("mateomenvielle@hotmail.com", "HUMEDAD INTERIOR  > 60%)!!! ", "LA HUMEDAD  ES MAYOR A 60(ESO NO ES BUENO --> Por encima de estos valores son frecuentes la aparición de hongos, mohó y trastornos alérgicos en los usuarios.");
 }
  
/*
En lo que respecta a la humedad, los estudios han demostrado que el nivel ideal de humedad en casa está en una franja comprendida entre el 40 % y el 60% 
de humedad relativa.Por debajo de estos valores empiezan a aparecer bacterias,virus y afecciones respiratorias, 
mientras que por encima son frecuentes la aparición de hongos, mohó y trastornos alérgicos en los usuarios.
 */

 if ( t < 20)
{
    Blynk.email("mateomenvielle@hotmail.com","ESP8266 ALERTA(TEMPERATURA INTERIOR < 20)!!!  ", "(ESO NO ES BUENO --> VAS A PASAR FRIO PROBABLEMENTE");

}

 else if ( t > 26)
{
    Blynk.email("mateomenvielle@hotmail.com","ESP8266 ALERTA(TEMPERATURA INTERIOR > 26)!!!", "(ESO NO ES BUENO --> VAS A PASAR CALOR PROBABLEMENTE");

}
 
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TemperaturaHumedadEXTERIOR()
{

  
 // Lee temperatura y humedad durante unos 250ms  (VARIABLES LOCALES!!!!)
  
  float t = dhtEXTERIOR.readTemperature();
  float h = dhtEXTERIOR.readHumidity();

  //SI FALLA LA LECTURA NO SIGO NO IMPRIMO NADA !!!
   if (isnan(t) || isnan(h)) 
   {
      Serial.println(" \t Fallo en la lectura \t");
      return;
   }   
  
  int TempEnt=t;
  int HumedadEnt=h;
//SOLUCION 

  int TEMPERATURAexterior = t*100;
  int HUMEDADexterior = h*100;


  //CADA VEZ QUE SE LLAMA EN PRIMERA INSTANCIA BORRO LO VIEJO !!!
  //CORRECCION PARA EL NO PARPADEO DEL DISPLAY DE LA TEMP Y HUMEDAD 

    //BORRO TEMP EXT
     tft.fillRect(126, 125,  65, 45, 0x0000);  // Draw filled rectangle (x,y,width,height,color)
     tft.fillRect(200, 125,36 , 45, 0x0000);  // Draw filled rectangle (x,y,width,height,color)
     tft.fillRect(182, 125, 19 , 37, 0x0000);
     
   
    //BORRO HUMEDAD EXT
     tft.fillRect(122, 232, 60 , 36, 0x0000);
     tft.fillRect(189, 232, 25 , 36, 0x0000);
     tft.fillRect(176, 232, 12 , 15, 0x0000);
    


  if (t<10)
  {
    tft.fillRect(126, 125, 23, 36, 0x0000);  // Draw filled rectangle (x,y,width,height,color)
    tft.setTextSize(6);  // Set text size. We are using custom font so you should always set text size as 0   
    tft.setCursor(157, 125);  // Set position (x,y)
    tft.setTextColor(0xFEF6);  // Set color of text. We are using custom font so there is no background color supported
    tft.println((TEMPERATURAexterior/100));  // IMPRIMO EL ENTERO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  
    tft.setTextSize(6);
    tft.setCursor(195, 125);  // Set position (x,y)
    tft.setTextColor(0xFEF6);  // Set color of text. We are using custom font so there is no background color supported
    tft.println(((TEMPERATURAexterior*0.01)-TempEnt)*10,0);  // IMPRIMO EL VALOR DECIMAL DESPUES DE LA COMA !!!!!!
  }
  else
  {
    tft.setTextSize(6);  // Set text size. We are using custom font so you should always set text size as 0   
    tft.setCursor(125, 125);  // Set position (x,y)
    tft.setTextColor(0xFEF6);  // Set color of text. We are using custom font so there is no background color supported
    tft.println((TEMPERATURAexterior/100));  // IMPRIMO EL ENTERO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  
    tft.setTextSize(6);
    tft.setCursor(200, 125);  // Set position (x,y)
    tft.setTextColor(0xFEF6);  // Set color of text. We are using custom font so there is no background color supported
    tft.println(((TEMPERATURAexterior*0.01)-TempEnt)*10,0);  // IMPRIMO EL VALOR DECIMAL DESPUES DE LA COMA !!!!!!
  }
//-------------------------------------------------------------
  
  if(h<10)
  {
    tft.fillRect(127, 232, 20, 36, 0x0000);  // Draw filled rectangle (x,y,width,height,color)
    tft.setTextSize(5);  // Set text size. We are using custom font so you should always set text size as 0   
    tft.setCursor(153, 232);  // Set position (x,y)
    tft.setTextColor(0xCFFE);  // Set color of text. We are using custom font so there is no background color supported
    tft.println(HUMEDADexterior/100);  // Print a text or value

    tft.setTextSize(5);
    tft.setCursor(189, 232);  // Set position (x,y)
    tft.setTextColor(0xCFFE);  // Set color of text. We are using custom font so there is no background color supported
    tft.println(((HUMEDADexterior*0.01)-HumedadEnt)*10,0);  // IMPRIMO EL VALOR DECIMAL DESPUES DE LA COMA !!!!!!
  }
  
  else
  {
    tft.setTextSize(5);  // Set text size. We are using custom font so you should always set text size as 0   
    tft.setCursor(127, 232);  // Set position (x,y)
    tft.setTextColor(0xCFFE);  // Set color of text. We are using custom font so there is no background color supported
    tft.println(HUMEDADexterior/100);  // Print a text or value

    tft.setTextSize(5);
    tft.setCursor(189, 232);  // Set position (x,y)
    tft.setTextColor(0xCFFE);  // Set color of text. We are using custom font so there is no background color supported
    tft.println(((HUMEDADexterior*0.01)-HumedadEnt)*10,0);  // IMPRIMO EL VALOR DECIMAL DESPUES DE LA COMA !!!!!!
  }

  
  
   Serial.print("Temperatura exterior: ");
   Serial.print(TEMPERATURAexterior);
   Serial.print(" *C ");
   Serial.print(" %\t");
   Serial.print("Humedad  exterior: ");
   Serial.print(HUMEDADexterior);
   Serial.print(" %\n");


   //IMPRIMO EN BLYNK

   lcd2.print(9,0,t);
   lcd2.print(12,1,h);

   /////////////////////////
//RANGOS DE HUMEDAD Y TEMP DE MI INTERES
   //https://actitudecologica.com/temperatura-de-confort-cual-es-temperatura-ideal-casa/

//JUEGO CON LOS VALORES LIMITES !!!
if (h < 20 )
{
  Blynk.email("mateomenvielle@hotmail.com", "HUMEDAD EXTERIOR < 20% ", "LA HUMEDAD ES MENOR A 20(ESO NO ES BUENO --> Por debajo de estos valores empiezan a aparecer bacterias,virus y afecciones respiratorias");
} 
 else if (h > 60) 
 {
   Blynk.email("mateomenvielle@hotmail.com", "HUMEDAD EXTERIOR > 60% ", "LA HUMEDAD ES MAYOR A 85(ESO NO ES BUENO --> Por encima de estos valores son frecuentes la aparición de hongos, mohó y trastornos alérgicos en los usuarios.");
 }
  
/*
En lo que respecta a la humedad, los estudios han demostrado que el nivel ideal de humedad en casa está en una franja comprendida entre el 40 % y el 60% 
de humedad relativa.Por debajo de estos valores empiezan a aparecer bacterias,virus y afecciones respiratorias, 
mientras que por encima son frecuentes la aparición de hongos, mohó y trastornos alérgicos en los usuarios.
 */

 if (t < 8)
{
    Blynk.email("mateomenvielle@hotmail.com", "TEMPERATURA EXTERIOR  < 8 ", "AFUERA HACE MUCHO FRIO");

}

 else if (t > 30)
{
    Blynk.email("mateomenvielle@hotmail.com", "TEMPERATURA EXTERIOR  > 30 ", "(AFURA HACE MUCHO CALOR");

}

  
}


void PRESION()
{
  //MySensorBMP.begin();
  //SDA VA A D2 ESP8266
  //SCL VA A D1 ESP8266
  
  
  
  float PRESION = 1022.4; //float PRESION = MySensorBMP.readPressure();

/*    Serial.print(" %\n");
 Serial.print("Presion = ");
 Serial.print(PRESION);
 Serial.println(" Pa");
 Serial.print(" %\n");

    
    Serial.print("Temperatura = ");
    Serial.print(MySensorBMP.readTemperature());
    Serial.println(" *C");
    
    Serial.print("Presion = ");
    Serial.print(MySensorBMP.readPressure()*0.01);
    Serial.println(" Pa");


    Serial.print("Presión a nivel del mar (calculado) = ");
    Serial.print(MySensorBMP.readSealevelPressure()*0.01);
    Serial.println(" HPa");*/

  tft.setCursor(87, 288);  // Set position (x,y)
  tft.setTextColor(0xFFFF);  // Set color of text. First is the color of text and after is color of background
  tft.setTextSize(3);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
  tft.println(PRESION);  // Print a text or value

  
}

////////////////////////////fin


///<---------------------------------------------------------------------------------------------------------------------------->

/*
EXPLICACION DE PRECION ATM BAJA

 por ej ::  999.2 hPa no supuerando los 1013 hPa punto de referencia que toman las estaciones meteorológicas como normal.

¿Qué significan estos valores y por qué deberían importarnos?  

Científicamente el problema se explica porque al aumentar la presión atmosférica, todos los espacios que contiene nuestro cuerpo sufren la diferencia que existe entre afuera y dentro, lo que favorece una expansión del volumen de aire, por ejemplo en los oídos, los senos nasales o los pulmones.

Cuándo se presenta esta combinación de baja presión y alta temperatura en algunas personas suelen aparecer dolores de cabeza, dolor en la cara y en los oídos, desgano y fatiga. 

Además aquellos que sufren de sinusitis crónica tienen la mayoría de los problemas, cuando el aire queda atrapado en los senos paranasales y es incapaz de igualar. Las personas que sufren de presión arterial alta también se ven afectadas por estos cambios atmosféricos. Otro factor a tener en cuenta es que afecta a las personas con artrosis,.

¿Qué debemos hacer en estos casos? Según indican los epecialistas lo mejor en estos casos es seguir una serie de consejos que ayudarán mientras dure el malestar y en caso de que persistan concurrir a una guardia médica.

Tomar abundante cantidad de agua;
Dormir lo necesario;
No saltearse las comidas;
Hacer ejercicio regularmente;
Aprender a manejar situaciones de estrés y
Evitar los alimentos cuya ingestión se asoció con dolores de cabeza. */
