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

}
