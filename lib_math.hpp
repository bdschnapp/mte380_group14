#ifndef __LIB_MATH_HPP__
#define __LIB_MATH_HPP__

#include "Arduino.h"

namespace math
{
    struct Vector3f
    {
        float x, y, z;
    };

    /**
     * Convert degrees to radians
     * @param deg degrees
     * @return radians
     */
    float deg_to_rad(float deg);

    /**
     * Convert radians to degrees
     * @param rad radians
     * @return degrees
     */
    float rad_to_deg(float rad);

    /**
     * Compare floats
     * @param f1 float 1 to compare
     * @param f2 float 2 to compare
     * @param margin error margin
     * @return returns true if abs(f1 - f2) < margin
     */
    bool float_compare(float f1, float f2, float margin = 1e-4f);


    /**
     * Clamps a given value into the range [lower_bound, upper_bound]
     * @param lower_bound the lower bound of the range to clamp into
     * @param upper_bound the upper bound of the range to clamp into
     * @param value the value to clamp
     * @return the clamped value as an element of the range [lower_bound, upper_bound] 
     */
    float clamp(const float lower_bound, const float upper_bound, const float value);
}

#endif