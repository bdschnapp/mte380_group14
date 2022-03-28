# About
This folder contains files for testing the PID controller. This is meant to be run on a laptop not an arduino.

## test_pid.cpp
This file can be used to validate the PID controller by experimenting with various Kp, Ki, and saturation limits.
This file implements a unit feedback control loop where the plant transfer function is 1 / (s+1). It uses
the PID controller code to generate a control signal.

## test_pi_viz.py
This file visualizes the signals output from test_pi.cpp

# To compile and run (For Linux)
g++ test_pid.cpp  ../../pid.cpp ../../lib_math.cpp -D LOCAL_BUILD && ./a.out && python test_pid_viz.py