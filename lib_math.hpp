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
     * Add two vectors
     * @param a vector 1
     * @param b vector 2
     * @return the equivalence of a + b
     */
    math::Vector3f operator+(const math::Vector3f &a, const math::Vector3f &b);

    /**
     * Subtract a vector from another vector
     * @param a vector 1
     * @param b vector 2
     * @return the equivalence of a - b
     */
    math::Vector3f operator-(const math::Vector3f &a, const math::Vector3f &b);

    /**
     * Converts vectors from imu frame to base link frame
     * This assumes the imu is rotated 90 deg ccw about its z-axis relative to the base link frame
     * @param v some vector in the imu frame 
     * @return equivalent vector in the base link frame
     */
    math::Vector3f transform_imu_data_to_base_frame(const math::Vector3f &theta);

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