#include "lib_math.hpp"

namespace math
{
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

}
