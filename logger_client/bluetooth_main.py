import bluetooth
import time

arduino_address = '98:D3:31:FD:B7:A7'

socket = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
print("connecting...")
socket.connect((arduino_address, 1))

print("connected")

raw_data = ""

record_time = 5
start_time = time.time()
print("recording data for " + str(record_time) + " seconds")

try:
    while (time.time() - start_time) < record_time:
        data = str(socket.recv(9600), encoding='ascii')
        raw_data += data

except Exception as e:
    print(str(e))

#print(raw_data)

data_array = []

data_array = raw_data.split("\n")

uss_array = []
usf_array = []
imu_t_x_array = []
imu_t_y_array = []
imu_t_z_array = []
imu_td_x_array = []
imu_td_y_array = []
imu_td_z_array = []

arrays = [uss_array, usf_array,
          imu_t_x_array, imu_t_y_array, imu_t_z_array,
          imu_td_x_array, imu_td_y_array, imu_td_z_array]
print("analyzing data")
for i in range(len(data_array)):
    if data_array[i] == "ultrasonic_front\r":
        usf_array.append(data_array[i+1])
    if data_array[i] == "ultrasonic_side\r":
        uss_array.append(data_array[i+1])

    if data_array[i] == "imu_t_x\r":
        imu_t_x_array.append(data_array[i+1])
    if data_array[i] == "imu_t_y\r":
        imu_t_y_array.append(data_array[i+1])
    if data_array[i] == "imu_t_z\r":
        imu_t_z_array.append(data_array[i+1])

    if data_array[i] == "imu_td_x\r":
        imu_td_x_array.append(data_array[i + 1])
    if data_array[i] == "imu_td_y\r":
        imu_td_y_array.append(data_array[i + 1])
    if data_array[i] == "imu_td_z\r":
        imu_td_z_array.append(data_array[i + 1])
print("printing to csv")
csv_array = []

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

csv = open("sensor_data.csv", "w+")
csv.write("USS, USF, IMU_T_X, IMU_T_Y, IMU_T_Z, IMU_TD_X, IMU_TD_Y, IMU_TD_Z\n")
for i in csv_array:
    csv.write(i)
csv.close()
print("done")


