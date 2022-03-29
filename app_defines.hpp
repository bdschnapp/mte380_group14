#ifndef MTE380_GROUP14_APP_DEFINES_HPP
#define MTE380_GROUP14_APP_DEFINES_HPP

#define PATH_LENGTH 11
constexpr float distances[PATH_LENGTH] = {0.21,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0};

/* tolerances */
#define DISTANCE_TOLERANCE 0.02f       // [m]
#define ANGULAR_TOLERANCE 0.05236f     // [rad] equivalent to 3 deg

/* Button Bin */
#define BUTTON_PIN 50

/* Side Ultrasonic Pins */
#define SIDE_ULTRASONIC_TRIG_PIN 45
#define SIDE_ULTRASONIC_ECHO_PIN 44

/* Front Ultrasonic Pins */
#define FRONT_ULTRASONIC_TRIG_PIN 43
#define FRONT_ULTRASONIC_ECHO_PIN 42

/* lateral controller */
constexpr float Kp_lat_us = 300.0f, Ki_lat_us = 0.0f, Kp_gyro = 350.0f, Ki_gyro = 0.0f;

/* This is a parameter you can change to experiment with different reliance ratios */
constexpr float GYRO_RELIANCE = 0.75f;

/* linear controller */
const float linear_Kp = 150;
const float linear_Ki = 3;

/* pivot controller */
const float pivot_Kp = 30;


#endif // MTE380_GROUP14_APP_DEFINES_HPP
