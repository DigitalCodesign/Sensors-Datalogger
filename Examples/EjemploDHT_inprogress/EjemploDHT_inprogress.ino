#include "DHT.h"

#define pinDHT 2

DHT dht(pinDHT, DHT11);

float temperatura;
float humedad;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  temperatura = dht.readTemperature();
  humedad = dht.readHumidity();
  float hic = dht.computeHeatIndex(temperatura, humedad, false);
  if (isnan(humedad) || isnan(temperatura)) {
    Serial.println("Error leyendo el sensor!");
    return;
  }
  else {
    Serial.print("Humedad: ");
    Serial.print(humedad);
    Serial.print("%  Temperatura: ");
    Serial.print(temperatura);
    Serial.print("°C ");
    Serial.print("°Sensacion termica: ");
    Serial.print(hic);
    Serial.print("°C ");
  }
  delay(1000);
}
