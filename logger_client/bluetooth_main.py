import bluetooth
import matplotlib.pyplot as pyplot
import time

sensor_address = '07:12:05:15:60:07'
socket = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
socket.connect((sensor_address, 1))

buffer = ""

while True:

    try:
        data = socket.recv(1024)
        buffer += str(data, encoding='ascii')

    except KeyboardInterrupt:
        print("disconnected")
        socket.close()
        break