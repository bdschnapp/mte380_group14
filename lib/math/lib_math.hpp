#ifndef __LIB_MATH_HPP__
#define __LIB_MATH_HPP__

#include "Arduino.h"

namespace math
{
    struct Vector3f
    {
        float x, y, z;
    };

    float deg_to_rad(float deg);

    float rad_to_deg(float rad);

    bool float_compare(float f1, float f2, float margin = 1e-4f);
}

#endif