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
     * An exponentially weighted moving average filter.
     * See wiki for definition: https://en.wikipedia.org/wiki/Moving_average#Exponential_moving_average
     * @param alpha decay factor of the ewma filter
     * @param prev the previous value of the filtered signal 
     * @param cur the current value of the raw signal
     * @return returns the filtered value
     */
    float ewma(const float alpha, const float prev, const float cur);
}

#endif