# Estación Meteorológica

Descripción

## Autores: 

- Augusto Samuel Hernández Martín
- José Luis González de Chávez 
- Miqueas Z. Fortes

## Materiales
- BMP280 I2C
- DHT22
- Arduino UNO
- Shield Protoboard Arduino UNO
- Portapilas 6F22
- Pila 6F22 9V
- Reloj RTc
- Módulo Tarjeta SD HW-125

## Conexiones

- BMP280: 
	- Vcc -> 3.3V
	- GND -> GND
	- SDA -> SDA
	- SCL -> SCL 
 - DHT22 (modulo con Rpull-up):
 	- Vcc -> 5V
 	- Do  -> D2
 	- GND -> GND

## Librerias

Debe instalarse lo siguiente:

- Librería DHT.h desarrollada por Adafruit (disponible de forma oficial en Gestor de Librerías)
- Librería BMP280_DEV (disponible en https://github.com/MartinL1/BMP280_DEV)

## Tools

- Se dispone de un escaner I2C para determinar las direcciones del BMP.
- Se dispone de un script en Python3 que recibe por consola el nombre del fichero a procesar (debe estar en misma ubicacion que el script). Lo procesa, genera las gráficas de los datos y las almacena en 'Medidas/Fecha', moviendo a dicha ruta el csv procesado.
