/*
   Código para Datalogger de un MQ-135 (CO2) y un DHT-22 (Tª y Humedad).
   Vuelca los datos en un fichero .CSV con nombre del instante que comienza a grabar.
   Autor: Augusto Samuel Hernández Martín
   GitHub: AugustoS97 (https://github.com/AugustoS97)
*/

/*  PINOUT MONTAJE EN ARDUINO UNO
    RTC:
      Vcc -> 5V
      GND -> GND
      SCL -> A5
      SDA -> A4
      
    Módulo LCD:
      Vcc -> 5V
      GND -> GND
      SCL -> A5
      SDA -> A4     

    Módulo SD:
      Vcc  -> 5V
      GND  -> GND
      MOSI -> D11
      SCK  -> D13
      MISO -> D12

    DHT22 (modulo con Rpull-up):
      Vcc -> 5V
      Do  -> D2
      GND -> GND
      
    MQ-135 (Sensor CO2):
      Vcc -> 5V
      Ao  -> A0
      GND -> GND

    LED Verde (Estatus LED)
      D3

    LED Rojo (Error LED)
      D4
*/

#include <SD.h>
#include <Wire.h>
#include <RTClib.h>
#include <DHT.h>
#include <BMP280_DEV.h> //BMP280 libreria
#include "MQ135.h"

#define PINLEDRECORDING 3
#define PINLEDERROR 4
#define DHTPIN 2     // Pin digital al que se conecta el sensor DHT22
#define PIN_MQ A0 //Pin analogico para MQ-135

#define PERIODO_MUESTREO 2000 //Se mide cada 2 segundos

#define DHTTYPE DHT11   // DHT 22

DHT dht(DHTPIN, DHTTYPE);

RTC_DS1307 rtc;
String segundo, minuto, hora, dia, mes;
String anio; //variable año
DateTime HoraFecha;

File logFile;
String nombreFichero;

float temperatura_bmp, presion_bmp, altitud_bmp;
BMP280_DEV bmp280; //Se define el sensor

void setup() {
  //Se configuran los pines de los LEDs como salidas
  pinMode(PINLEDRECORDING, OUTPUT);
  pinMode(PINLEDERROR, OUTPUT);

  //En el arranque se encienden los dos LEDS
  digitalWrite(PINLEDRECORDING, HIGH);
  digitalWrite(PINLEDERROR, HIGH);

  dht.begin();

  Serial.begin(9600);

  rtc.begin(); //Inicializamos el RTC

  Serial.print(F("Iniciando SD ..."));
  while (!SD.begin(9)){
    Serial.println(F("Error al iniciar"));
    return;
  }
  Serial.println(F("Iniciado correctamente"));

  //Creamos el nombre del fichero donde guardar los datos
  HoraFecha = rtc.now(); //obtenemos la hora y fecha actual
  if (HoraFecha.second() < 10) {
    segundo = "0" + String(HoraFecha.second());
  }
  else {
    segundo = String(HoraFecha.second());
  }

  if (HoraFecha.minute() < 10) {
    minuto = "0" + String(HoraFecha.minute());
  }
  else {
    minuto = String(HoraFecha.minute());
  }

  if (HoraFecha.hour() < 10) {
    hora = "0" + String(HoraFecha.hour());
  }
  else {
    hora = String(HoraFecha.hour());
  }

  if (HoraFecha.day() < 10) {
    dia = "0" + String(HoraFecha.day());
  }
  else {
    dia = String(HoraFecha.day());
  }
  if (HoraFecha.month() < 10) {
    mes = "0" + String(HoraFecha.month());
  }
  else {
    mes = String(HoraFecha.month());
  }

  anio = String(HoraFecha.year());


  //nombreFichero = String(mes) + String(dia) + String(hora) + String(minuto) + ".csv";
  //Se crea un nombre regular de la forma MMDDHHmm.csv
  nombreFichero = mes + dia + hora + minuto + ".csv";

  //Se abre el fichero para crear la cabecera del .CSV
  logFile = SD.open( nombreFichero, FILE_WRITE);
  if (logFile) { //Si se puede abrir el fichero
    Serial.print("Creado correctamente :");
    Serial.println(nombreFichero);
    logFile.println("TimeStamp,Humedad (%), Temperatura(DHT), Temperatura (BMP), Presion (hPa), Altitud (m), CO2 (ppm)"); //Se escribe la cabecera del .CSV
    logFile.close(); //Cierro el fichero al acabar de escribir todos los elementos
  }

  //Inicializamos el sensor BMP280 y lo configuramos
  bmp280.begin(BMP280_I2C_ALT_ADDR); //Se inicializa con la direccion 0x76
  bmp280.setTimeStandby(TIME_STANDBY_250MS); //Se configura el tiempo entre medidas
  bmp280.startNormalConversion(); //Se hace trabajar en modo continuo, medida tras medida...

  //Al acabar el arranque se apagan los dos LEDs
  digitalWrite(PINLEDRECORDING, LOW);
  digitalWrite(PINLEDERROR, LOW);
}


// Funcion que simula la lectura de un sensor
int readSensor() {
  return 0;
}

void loop() {
  //Obtenemos el instante de tiempo
  HoraFecha = rtc.now(); //obtenemos la hora y fecha actual
  segundo = String(HoraFecha.second());
  minuto = String(HoraFecha.minute());
  hora = String(HoraFecha.hour());
  dia = String(HoraFecha.day());
  mes = String(HoraFecha.month());
  anio = String(HoraFecha.year());

  //Inicializamos el sensor MQ-135
  MQ135 gasSensor = MQ135(PIN_MQ); // Vinculamos el sensor al pin A0

  //Se leen los sensores
  int value = readSensor();

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  //Se lee la concentracion de CO2 (en ppm)
  float CO2ppm = gasSensor.getPPM(); //Se obtiene la medida de Co2

  //Se lee el BMP y se guardan los valores
  bmp280.getCurrentMeasurements(temperatura_bmp, presion_bmp, altitud_bmp);
  // Abrir archivo .csv con la fecha de arranque y escribir valor
  logFile = SD.open(nombreFichero, FILE_WRITE);
  if (logFile) { //Si se puede abrir el fichero
    //Se enciende el LED para indicar que se ha abierto correctamente
    digitalWrite(PINLEDRECORDING, HIGH);
    digitalWrite(PINLEDERROR, LOW);
    String timeStamp = String(anio) + ":" + String(mes) + ":" + String(dia)
                       + ":" + String(hora) + ":" + String(minuto) + ":" + String(segundo);

    //Escribimos todos los valores medidos en el CSV
    logFile.print(timeStamp);
    logFile.print(",");
    if (!isnan(h) && !isnan(t)) { //Escribimos todos los valores solo si no hay errores de lectura
      logFile.print(h);
      logFile.print(",");
      logFile.print(t);
      logFile.print(",");
      logFile.print(temperatura_bmp);
      logFile.print(",");
      logFile.print(presion_bmp);
      logFile.print(",");
      logFile.print(altitud_bmp);
      logFile.print(",");
      logFile.println(CO2ppm);
      Serial.println("Datos almacenados correctamente");
      Serial.print("H:");
      Serial.print(h);
      Serial.print(" T:");
      Serial.print(t);
      Serial.print(" P:");
      Serial.print(presion_bmp);
      Serial.print(" A:");
      Serial.print(altitud_bmp);
      Serial.print(" [CO2]:");
      Serial.println(CO2ppm);
    }
    logFile.close(); //Cierro el fichero al acabar de escribir todos los elementos
  }
  else { //Si no se puede abrir correctamente el fichero CSV
    digitalWrite(PINLEDRECORDING, LOW);
    digitalWrite(PINLEDERROR, HIGH);
    Serial.println("Error al abrir el archivo");
  }

  //Al finalizar se apagan los dos LEDs
  digitalWrite(PINLEDRECORDING, LOW);
  digitalWrite(PINLEDERROR, LOW);

  delay(PERIODO_MUESTREO); //Se espera el tiempo de meustreo para la siguiente medida
}
