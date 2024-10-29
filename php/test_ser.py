import serial
import time

ser = serial.Serial(port='COM3', baudrate='115200', timeout=0)

while (True):
    logger = ser.readline()
    if "temperature" or "humidity" or "pressure " in logger:
        temperature = logger[6:11].decode('ascii')
        humidity = logger[23:30].decode('ascii')
        pressure = logger[49:55].decode('ascii')
        print(f"temperature = {temperature}, humidity = {humidity}, pressure = {pressure}")

    time.sleep(1)



ser.close()