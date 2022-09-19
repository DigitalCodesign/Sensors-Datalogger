# Estación Meteorológica

Dispositivo de captura de datos y almacenamiento de los mismos en tarjeta SD. Está basado en Arduino.
Incorpora una herramienta en Python para proceder a la representación gráfica de los datos.

## Autores: 

- Augusto Samuel Hernández Martín
- José Luis González de Chávez 
- Miqueas Z. Fortes

## Materiales
- [BMP280 I2C](https://www.digitalcodesign.com/shop/00016148-sensor-de-presion-y-temperatura-bmp280-3959?search=bmp280#attr=)
- [DHT22](https://www.digitalcodesign.com/shop/00016131-modulo-con-sensor-de-temperatura-y-humedad-dht22-3958?search=dht22#attr=)
- [Arduino UNO](https://www.digitalcodesign.com/shop/00017114-placa-compatible-con-arduino-uno-r3-4056?search=arduino#attr=)
- [Shield Protoboard Arduino UNO](https://www.digitalcodesign.com/shop/00016889-shield-protoboard-170-puntos-v-5-para-arduino-uno-4033?search=shield)
- [Portapilas 6F22](https://www.digitalcodesign.com/shop/00010528-adaptador-pila-9v-6f22-con-conector-dc-3397?search=6f22#attr=)
- [Pila 6F22 9V](https://www.digitalcodesign.com/shop/00010498-duracell-dur01925-pila-alcalina-plus-power-9v-6f22-3394?search=6f22#attr=)
- [Reloj RTC DS1307](https://www.digitalcodesign.com/shop/00016520-modulo-reloj-rtc-ds1307-at24c32-compatible-con-arduino-3997?search=rtc#attr=)
- [Módulo Tarjeta SD HW-125](https://www.digitalcodesign.com/shop/00016513-modulo-lector-tarjeta-micro-sd-hw-125-3996?search=hw-125#attr=)

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
- Librería [BMP280_DEV](https://github.com/MartinL1/BMP280_DEV)

## Tools

- Se dispone de un escaner I2C para determinar las direcciones del BMP.
- Se dispone de un script en Python3 que recibe por consola el nombre del fichero a procesar (debe estar en misma ubicacion que el script). Lo procesa, genera las gráficas de los datos y las almacena en 'Medidas/Fecha', moviendo a dicha ruta el csv procesado.
