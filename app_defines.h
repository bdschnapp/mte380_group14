#ifndef MTE380_GROUP14_APP_DEFINES_HPP
#define MTE380_GROUP14_APP_DEFINES_HPP


#define PATH_LENGTH 11
extern int distances[PATH_LENGTH];

// unit [cm]
// TODO: add path data
distances = {0,
             0,
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
// unit [cm]
#define DISTANCE_TOLERANCE 1
#define ANGULAR_TOLERANCE 1

// TODO: add button pin
#define BUTTON_PIN

/* Side Ultrasonic Pins */
#define SIDE_ULTRASONIC_TRIG_PIN 10
#define SIDE_ULTRASONIC_ECHO_PIN 11

/* Front Ultrasonic Pins */
#define FRONT_ULTRASONIC_TRIG_PIN 12
#define FRONT_ULTRASONIC_ECHO_PIN 13

#endif //MTE380_GROUP14_APP_DEFINES_HPP