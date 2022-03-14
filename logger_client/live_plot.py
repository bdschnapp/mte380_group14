import bluetooth
import time
import queue
import threading
import matplotlib.pyplot as plt

# queue
global Q

# array of strings
global sensor_list

# dict
global sensors

# plotting objects
global fig
global sub_plt

sensor_list = ["usf",
               "uss",
               "tx",
               "ty",
               "tz",
               "tdx",
               "tdy",
               "tdz"
               ]
sensors = {}


def bluetooth_init():
    arduino_address = '98:D3:31:FD:B7:A7'
    socket = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
    print("connecting...")
    socket.connect((arduino_address, 1))
    print("connected")
    return socket


def bluetooth_read(socket, baud):
    raw_data = ""
    while 1:
        data = str(socket.recv(baud), encoding='ascii')
        raw_data += data

        for _ in range(raw_data.count("\n")):
            index = raw_data.find("\n")
            Q.put(raw_data[:index], block=True)


def live_plot():
    while 1:
        header = Q.get(block=True)

        if header in sensors.keys():
            data = Q.get(block=True)
            sensors[header].append(data)
            time_now = time.time()

            for j in range(len(sensor_list)):
                if sensor_list[j] == header:
                    sub_plt[j].scatter(time_now, data)

        # this might break things depending on the speed which Q is filled
        if Q.empty():
            plt.pause(1/100)


if __name__ == '__main__':
    bt = bluetooth_init()
    Q = queue.Queue(50)
    for i in sensor_list:
        sensors[i] = []

    fig, sub_plt = plt.subplots(len(sensor_list, 1))

    read = threading.Thread(target=bluetooth_read, args=(bt, 9600,))
    plot = threading.Thread(target=live_plot)

    read.start()
    plot.start()

    while 1:
        try:
            time.sleep(0.5)

        except KeyboardInterrupt:
            break

    read.join()
    plot.join()
    fig.show()

    # save data to a csv
    csv_array = []
    arrays = []

    # convert dict to list cause i dont like ditcs
    for i in sensors.keys():
        arrays.append(sensors[i])

    # bibity bopity boop copy code go zoop
    max_length = 0
    for i in arrays:
        if len(i) > max_length:
            max_length = len(i)

    for i in range(max_length):
        formatted_string = ""
        for j in arrays:
            try:
                formatted_string += j[i][:-1] + ", "
            except:
                formatted_string += ", "
        formatted_string += "\n"

        csv_array.append(formatted_string)

    file_time = time.time()
    csv = open("" + str(file_time) + "_live_plot", "w+")

    header_str = ""
    for i in sensors:
        header_str += i + ", "
    header_str = header_str[:-2] + "\n"
    csv.write(header_str)

    for i in csv_array:
        csv.write(i)

    csv.close()
