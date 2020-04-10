#include <SFE_BMP180.h> //libreria del sensor
#include <Wire.h>

char status;         // funcion de estado del sensor
double tem,presion;   //varables

SFE_BMP180 sensorPresion;

void setup()
{
  Serial.begin(9600);
  sensorPresion.begin();
}
void loop()
{
  status = sensorPresion.startTemperature();  //inicia el envio del pulso para leer la temperatura
  delay(status);                              //delay de proteccion sino obtiene una señal no sigue el programa
  sensorPresion.getTemperature(tem);         // obtenemos la temperatura
  status = sensorPresion.startPressure(3);   //inicia el envio del pulso para leer la presion
  delay(status);                              //delay de proteccion sino obtiene una señal no sigue el programa
  sensorPresion.getPressure(presion,tem);   // obtenemos la presion
  Serial.print("Presion atmosferica:  ");     // imprime el texto en el monitor
  Serial.print(presion*0.1,2);             // conversion de milibares a Kpa
  Serial.println( " KPa");  
  delay(500);                              //llemos cada 500ms
}
