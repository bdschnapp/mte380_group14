#include "Arduino.h"

/* Uncomment the macro for the application you are looking to test */
//#define NONE
// #define APP_MAIN
// #define TEST_LIB_MATH
// #define TEST_DEV_BNO055
// #define TEST_DEV_ULTRASONIC
#define TEST_DEV_BUTTON
// #define TEST_LINEAR_CONTROLLER
// #define TEST_LATERAL_CONTROLLER
// #define TEST_PIVOT_CONTROLLER
// #define TEST_DEV_TB9051FTG
// #define TEST_DRIVETRAIN

/* Bring in the appropriate application header file */
#ifdef NONE
/* import nothing, but define empty functions */
void app_setup() {}
void app_loop() {}

#elif defined(APP_MAIN)
#include "app_main.hpp";
using namespace main;

#elif defined(TEST_LIB_MATH)
#include "test_lib_math.hpp"
using namespace test_lib_math;
#elif defined(TEST_DEV_BNO055)
#include "test_dev_bno055.hpp"
using namespace test_dev_bno055;
#elif defined(TEST_DEV_ULTRASONIC)
#include "test_dev_ultrasonic.hpp"
using namespace test_dev_ultrasonic;
#elif defined(TEST_LINEAR_CONTROLLER)
#include "test_linear_controller.hpp"
using namespace test_linear_controller;
#elif defined(TEST_LATERAL_CONTROLLER)
#include "test_lateral_controller.hpp"
using namespace test_lateral_controller;
#elif defined(TEST_PIVOT_CONTROLLER)
#include "test_pivot_controller.hpp"
using namespace test_pivot_controller;
#elif defined(TEST_DEV_TB9051FTG)
#include "test_dev_TB9051FTG.hpp"
using namespace test_dev_TB9051FTG;
#elif defined(TEST_DRIVETRAIN)
#include "test_drivetrain.hpp"
using namespace test_drivetrain;
#elif defined(TEST_DEV_BUTTON)
#include "test_dev_button.hpp"
using namespace test_dev_button;

#else
/* Should never get here. If it does, you might be missing a condition */
static_assert(false);
#endif

long time_us;

void setup()
{
    app_setup();
}

void loop()
{
    time_us = micros();
    
    app_loop();
    
    delayMicroseconds(10000 - (micros() - time_us));
}
