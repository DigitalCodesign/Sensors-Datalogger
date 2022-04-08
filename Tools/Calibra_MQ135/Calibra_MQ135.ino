/* 
 *  Codigo para obtener el valor de R0 y poder calibrar el sensor modificando la libreria
 *  Seguir instrucciones de: 
 *  https://circuitdigest.com/microcontroller-projects/interfacing-mq135-gas-sensor-with-arduino-to-measure-co2-levels-in-ppm
 */

#include "MQ135.h"

void setup () {
  Serial.begin (9600);
}

void loop() {
  MQ135 gasSensor = MQ135(A0); // Attach sensor to pin A0
  float rzero = gasSensor.getRZero();
  Serial.println (rzero);
  delay(1000);
}
