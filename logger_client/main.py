# pip install arduino-simple-rpc
# pip install matplotlib

from simple_rpc import SocketInterface as Interface
from serial.urlhandler import protocol_socket
import matplotlib.pyplot as pyplot
import time


ip_addr = "192.168.1.1:80"

protocol_socket.time.sleep = lambda x: None
interface = Interface('socket://' + ip_addr)

if interface.ping(10) == 10:
    pass

data = []

while interface.ping(1):
    time.sleep(1)
    data.append(interface.get_data())

pyplot.plot(data)
