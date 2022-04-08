#include <SD.h>
#include <Wire.h>
#include "RTClib.h"
#include "DHT.h"
#include <BMP280_DEV.h> //BMP280 libreria

#define PINLEDRECORDING 3
#define PINLEDERROR 4
#define DHTPIN 2     // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

RTC_DS1307 rtc;
int segundo, minuto, hora, dia, mes;
long anio; //variable año
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
  if (!SD.begin(9))
  {
    Serial.println(F("Error al iniciar"));
    return;
  }
  Serial.println(F("Iniciado correctamente"));

  //Creamos el nombre del fichero donde guardar los datos
  HoraFecha = rtc.now(); //obtenemos la hora y fecha actual
  segundo = HoraFecha.second();
  minuto = HoraFecha.minute();
  hora = HoraFecha.hour();
  dia = HoraFecha.day();
  mes = HoraFecha.month();
  anio = HoraFecha.year();


  nombreFichero = String(mes) + String(dia) + String(hora) + String(minuto) + ".csv";

  //Se abre el fichero para crear la cabecera del .CSV
  logFile = SD.open( nombreFichero, FILE_WRITE);
  if (logFile) { //Si se puede abrir el fichero
    Serial.print("Creado correctamente :");
    Serial.println(nombreFichero);
    logFile.println("TimeStamp, Humedad, Temperatura"); //Se escribe la cabecera del .CSV
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
  segundo = HoraFecha.second();
  minuto = HoraFecha.minute();
  hora = HoraFecha.hour();
  dia = HoraFecha.day();
  mes = HoraFecha.month();
  anio = HoraFecha.year();

  //Se leen los sensores
  int value = readSensor();

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  //Se lee el BMP y se guardan los valores. Si hay un error se ponen los valores de cero
  /*if (!bmp280.getMeasurements(temperatura_bmp, presion_bmp, altitud_bmp)) {
    temperatura_bmp = 0.0;
    presion_bmp = 0.0;
    altitud_bmp = 0.0;
  }*/
  bmp280.getMeasurements(temperatura_bmp, presion_bmp, altitud_bmp);
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
    //if (!isnan(h) && !isnan(t)) {
    logFile.print(h);
    logFile.print(",");
    logFile.print(t);
    logFile.print(",");
    logFile.print(temperatura_bmp);
    logFile.print(",");
    logFile.print(presion_bmp);
    logFile.print(",");
    logFile.println(altitud_bmp);
    //}
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
  delay(2000); //Se mide cada 2000 ms
}
