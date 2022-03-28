#ifndef __LIB_MATH_HPP__
#define __LIB_MATH_HPP__

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

    /**
     * Clamps a given value into the range [lower_bound, upper_bound]
     * @param lower_bound the lower bound of the range to clamp into
     * @param upper_bound the upper bound of the range to clamp into
     * @param value the value to clamp
     * @return the clamped value as an element of the range [lower_bound, upper_bound]
     */
    float clamp(const float lower_bound, const float upper_bound, const float value);

    /**
     * linear interpolation between 2 values
     * @param start the starting value of the interpolation
     * @param end the end value of the interpolation
     * @param alpha a value from 0 to 1 of where to interpolate in the range
     * @return the value at alpha in a linear rnage from start to end
     */
    float lerp(const float start, const float end, const float alpha);

    /**
     * inverse of lerp, returns the alpha value from 0 to 1 of where
     * a number lies between the start and end points
     * @param start lower bound of the range
     * @param end upper bound of the range
     * @param value the value to unlerp in the given range
     * @return the distance of the value from start to end from 0 to 1
     */
    float unlerp(const float start, const float end, const float value);

    /**
     * remaps a value from one range to another using linear interpolation
     * @param old_start start of the range of the given value
     * @param old_end end of the range of the given value
     * @param old_value the value to be remapped
     * @param new_start start of the range to remap to
     * @param new_end end of the range to remap to
     * @return a value proportional to old_value remapped to the given new range
     */
    float remap(const float old_start, const float old_end, const float old_value,
                const float new_start, const float new_end);
}

#endif