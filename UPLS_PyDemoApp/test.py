import serial
import time

ser = serial.Serial('/dev/ttyTHS4')
ser.write(b'hello')
time.sleep(0.5)
msg = ser.read(10)
print(msg)
ser.close()