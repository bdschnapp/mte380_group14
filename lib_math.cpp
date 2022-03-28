#include "lib_math.hpp"

#ifndef LOCAL_BUILD
#include "Arduino.h"
#else
/* Replace arduino functions with std cpp functions */
#include <algorithm>
using std::abs;
using std::max;
using std::min;
constexpr auto PI = 3.14159265f;
#endif

namespace math
{
    math::Vector3f operator+(const math::Vector3f &a, const math::Vector3f &b)
    {
        return {a.x + b.x, a.y + b.y, a.z + b.z};
    }

    math::Vector3f operator-(const math::Vector3f &a, const math::Vector3f &b)
    {
        const math::Vector3f neg_b = {-b.x, -b.y, -b.z};
        return a + neg_b;
    }

    math::Vector3f transform_imu_data_to_base_frame(const math::Vector3f &theta)
    {
        return {theta.y, theta.x, theta.z};
    }

    float deg_to_rad(float deg)
    {
        return deg * PI / 180.0f;
    }

    float rad_to_deg(float rad)
    {
        return rad * 180.0f / PI;
    }

    bool float_compare(float f1, float f2, float margin)
    {
        return (abs(f1 - f2) < margin);
    }

    float ewma(const float alpha, const float prev, const float cur)
    {
        return alpha * cur + (1 - alpha) * prev;
    }

    float clamp(const float lower_bound, const float upper_bound, const float value)
    {
        return min(max(lower_bound, value), upper_bound);
    }

    float lerp(const float start, const float end, const float alpha){
        return start * (1.0 - alpha) + end * alpha;
    }

    float unlerp(const float start, const float end, const float value){
        return (value - start) / (end - start);
    }

    float remap(const float old_start, const float old_end, const float old_value,
                const float new_start, const float new_end){
        return lerp(new_start, new_end, unlerp(old_start, old_end, old_value));
    }
}
