#ifndef MTE380_GROUP14_APP_DEFINES_HPP
#define MTE380_GROUP14_APP_DEFINES_HPP

#define PATH_LENGTH 11
constexpr float distances[PATH_LENGTH] = {0,
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

// TODO: create actual tolerances
#define DISTANCE_TOLERANCE 0.02f       // [m]
#define ANGULAR_TOLERANCE 0.05236f     // [rad] equivalent to 3 deg

// TODO: add button pin
#define BUTTON_PIN

/* Side Ultrasonic Pins */
#define SIDE_ULTRASONIC_TRIG_PIN 44
#define SIDE_ULTRASONIC_ECHO_PIN 45

/* Front Ultrasonic Pins */
#define FRONT_ULTRASONIC_TRIG_PIN 43
#define FRONT_ULTRASONIC_ECHO_PIN 42

#endif // MTE380_GROUP14_APP_DEFINES_HPP
