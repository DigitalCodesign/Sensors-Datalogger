# Estación Meteoroligca Cefiro

Proyecto desarrollado para el IES Güimar para implementar una estación meteorológica con volcado de datos a la red a través del servicio web de Thingspeak y su API de acceso gratuito.

## Autores: 
- José Luis González de Chávez 
- Augusto Samuel Hernández Martín

## Materiales
- BMP280 I2C
- DHT22
- Wemos D1 R1
- Shield Protoboard Arduino UNO
- Portapilas 6F22
- Pila 6F22 9V
- Display 16x02 I2C

## Conexiones

- BMP280: 
	- Vcc -> 3.3V
	- GND -> GND
	- SDA -> SDA (D4)
	- SCL -> SCL (D3)
 - LCD 16x02 I2C:
 	- Vcc -> 5V
 	- GND -> GND
 	- SDA -> SDA (D4)
 	- SCL -> SCL (D3)
 - DHT22 (modulo con Rpull-up):
 	- Vcc -> 3.3V
 	- Do  -> D5 (GPIO14)
 	- GND -> GND

## Librerias

Debe instalarse lo siguiente:

- Placas Wemos D1 desde el Gestor de Placas de Arduino, añadiendo previamente el enlace de consulta: http://arduino.esp8266.com/stable/package_esp8266com_index.json
- Librería DHT.h desarrollada por Adafruit (disponible de forma oficial en Gestor de Librerías)
- Librería BMP280_DEV (disponible en https://github.com/MartinL1/BMP280_DEV)
- Librería LiquidCrystal I2C disponible en el Gestor de Librerias

## Tools

- Se dispone de un escaner I2C para determinar las direcciones del BMP y del PCF8574 del Display LCD.