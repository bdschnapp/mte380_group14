#ifndef MTE380_GROUP14_APP_DEFINES_HPP
#define MTE380_GROUP14_APP_DEFINES_HPP

#define PATH_LENGTH 11

#define FIRST_LONGITUDINAL_GOAL_DISTANCE 0.10f
#define SECOND_LONGITUDINAL_GOAL_DISTANCE 0.38f
#define THIRD_LONGITUDINAL_GOAL_DISTANCE 0.68f
constexpr float distances[PATH_LENGTH] = {FIRST_LONGITUDINAL_GOAL_DISTANCE,
                                          FIRST_LONGITUDINAL_GOAL_DISTANCE,
                                          FIRST_LONGITUDINAL_GOAL_DISTANCE,
                                          SECOND_LONGITUDINAL_GOAL_DISTANCE,
                                          SECOND_LONGITUDINAL_GOAL_DISTANCE,
                                          SECOND_LONGITUDINAL_GOAL_DISTANCE,
                                          SECOND_LONGITUDINAL_GOAL_DISTANCE,
                                          THIRD_LONGITUDINAL_GOAL_DISTANCE,
                                          THIRD_LONGITUDINAL_GOAL_DISTANCE,
                                          THIRD_LONGITUDINAL_GOAL_DISTANCE,
                                          THIRD_LONGITUDINAL_GOAL_DISTANCE};

#define FIRST_LATERAL_GOAL_DISTANCE 0.12f
#define SECOND_LATERAL_GOAL_DISTANCE 0.41f
#define THIRD_LATERAL_GOAL_DISTANCE 0.71f

constexpr float lateral_distances[PATH_LENGTH] = {FIRST_LATERAL_GOAL_DISTANCE,
                                                  FIRST_LATERAL_GOAL_DISTANCE,
                                                  FIRST_LATERAL_GOAL_DISTANCE,
                                                  FIRST_LATERAL_GOAL_DISTANCE,
                                                  SECOND_LATERAL_GOAL_DISTANCE,
                                                  SECOND_LATERAL_GOAL_DISTANCE,
                                                  SECOND_LATERAL_GOAL_DISTANCE,
                                                  SECOND_LATERAL_GOAL_DISTANCE,
                                                  THIRD_LATERAL_GOAL_DISTANCE,
                                                  THIRD_LATERAL_GOAL_DISTANCE,
                                                  THIRD_LATERAL_GOAL_DISTANCE};

// TODO: create actual tolerances
#define DISTANCE_TOLERANCE 0.02f   // [m]
#define ANGULAR_TOLERANCE 0.05236f // [rad] equivalent to 3 deg

// TODO: add button pin
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
const float linear_Kp = 100;
const float linear_Ki = 0; // CAUTION: Linear controller currently cant handle integral control
#define LINEAR_DEBOUNCE 15
#define LINEAR_MIN_GAS 0
#define LINEAR_MAX_GAS 100
#define LINEAR_RAMP_UP_ITERATIONS 10

/* pivot controller */
const float pivot_Kp = 35;
const float pivot_Ki = 0;
#define PIVOT_DEBOUNCE 5
#define MIN_PIVOT_POWER -100
#define MAX_PIVOT_POWER 100

#define PIT_DELAY_MS 3000
#define PIT_SPEED 50
#define PIT_PITCH_TOLERANCE 0.10472f


#endif // MTE380_GROUP14_APP_DEFINES_HPP
