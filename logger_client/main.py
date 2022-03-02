# pip install arduino-simple-rpc
# pip install pyserial
# pip install numpy

from simple_rpc import SocketInterface as Interface
from serial.urlhandler import protocol_socket
import time
import numpy as np

ip_addr = "192.168.1.1:80"

protocol_socket.time.sleep = lambda x: None
interface = Interface('socket://' + ip_addr)

if interface.ping(10) == 10:
    pass

data = []

while interface.ping(1):
    time.sleep(1)
    data.append(interface.get_data())

# do some pretty stuff to analyze/graph the data