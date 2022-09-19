"""
PROCESA CSV PYTHONCODE

Código para procesar el fichero .CSV generado por el Arduino y almacenado en la Tarjeta SD.
A la hora de ejecutar el código debe modificarse en este SCRIPT la linea filename e introducir el
nombre del fichero a procesar. El script se encarga de procesarlo, generar los gráficos y mover el fichero
procesado al directorio de su fecha 

La estructura de ficheros generada es:
    - Medidas
        - YYYYMMDD
            - Graficos con hora de inicio
            - Fichero .csv con hora de inicio

Autor: Augusto Samuel Hernández Martín

"""


import csv
import numpy as np
import matplotlib.pyplot as plt
import os
from pathlib import Path
import shutil #Para mover ficheros
import sys #Para pasar argumentos al ejecutar script


if (len(sys.argv) < 2):
    filename = '04092121.csv'
else:
    filename = sys.argv[1]

filepath = os.path.join("Medidas", "2022" + filename[2:4] + filename[0:2] )

Time = np.array([])
Humedad = np.array([], dtype=float)
TemperaturaDHT = np.array([], dtype=float)
TemperaturaBMP = np.array([], dtype=float)
Presion = np.array([], dtype=float)
COdos = np.array([], dtype=float)

with open(filename) as File:
    reader = csv.reader(File, delimiter=',', quotechar=',', quoting=csv.QUOTE_MINIMAL)
    next(reader)
    for row in reader:
        Time = np.append(Time, (row[0][9:len(row[0])]))
        Humedad = np.append(Humedad, float(row[1]))
        TemperaturaDHT = np.append(TemperaturaDHT, float(row[2]))
        TemperaturaBMP = np.append(TemperaturaBMP, float(row[3]))
        Presion = np.append(Presion, float(row[4]))
        COdos = np.append(COdos, float(row[6]))
        ##print(row)

#Se crea el directorio de destino
path = Path (os.path.join(os.path.abspath(os.getcwd()),  filepath))
path.mkdir(parents = True, exist_ok = True)

# Representacion de humedad
plt.figure(figsize=(32,18))
plt.plot(Time, Humedad)
plt.xticks(Time, rotation = '45')
plt.margins(0.1)
plt.title(filename[0:2] + ' de ' + filename[2:4] + ' de 2022')
plt.xlabel('Hora de la medición')
plt.ylabel('Humedad %')
plt.savefig(os.path.join(path, filename[0:-4] + '_Humidity.png'), dpi = 'figure', bbox_inches='tight')
#plt.show()

# Representacion de temperatura BMP
plt.figure(figsize=(32,18))
plt.plot(Time, TemperaturaBMP)
plt.xticks(Time, rotation = '45')
plt.margins(0.1)
plt.title(filename[0:2] + ' de ' + filename[2:4] + ' de 2022')
plt.xlabel('Hora de la medición')
plt.ylabel('Temperatura ºC')
plt.savefig(os.path.join(path, filename[0:-4] + '_Temperature.png'), dpi = 'figure', bbox_inches='tight')
#plt.show()
print(COdos)

# Representacion de la [Co2] en ppm
plt.figure(figsize=(32,18))
plt.plot(Time, COdos)
plt.xticks(Time, rotation = '45')
plt.margins(0.1)
plt.title(filename[0:2] + ' de ' + filename[2:4] + ' de 2022')
plt.xlabel('Hora de la medición')
plt.ylabel('Concentración de CO2 [ppm]')
plt.savefig(os.path.join(path, filename[0:-4] + '_CO2.png'), dpi = 'figure', bbox_inches='tight')
#plt.show()

#Se mueve el fichero procesado a la carpeta medidas.
shutil.move(filename, os.path.join(filepath, filename))