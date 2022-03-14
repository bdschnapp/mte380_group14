#include "Arduino.h"

/* Uncomment the macro for the application you are looking to test */
#define NONE
// #define TEST_LIB_MATH
// #define TEST_DEV_BNO055
// #define TEST_DEV_ULTRASONIC
// #define TEST_DEV_BUTTON

/* Bring in the appropriate application header file */
#ifdef NONE
/* import nothing, but define empty functions */
void app_setup() {}
void app_loop() {}
#elif defined(TEST_LIB_MATH)
#include "test_lib_math.hpp"
using namespace test_lib_math;
#elif defined(TEST_DEV_BNO055)
#include "test_dev_bno055.hpp"
using namespace test_dev_bno055;
#elif defined(TEST_DEV_ULTRASONIC)
#include "test_dev_ultrasonic.hpp"
using namespace test_dev_ultrasonic;
#elif defined(TEST_DEV_TB9051FTG)
#include "test_dev_TB9051FTG.hpp"
using namespace test_dev_TB9051FTG;
#elif defined(TEST_DEV_BUTTON)
#include "test_dev_button.hpp"
using namespace test_dev_button;
#else
/* Should never get here. If it does, you might be missing a condition */
static_assert(false);
#endif

void setup()
{
    app_setup();
}

void loop()
{
    app_loop();
}
