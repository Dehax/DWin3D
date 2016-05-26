#pragma once

#include "../DWin3DLib_global.h"
#include <cmath>
#include "Vec3f.h"

struct DWIN3DLIB_API Vec3i
{
public:
    explicit Vec3i(int x, int y, int z);
    Vec3i(const Vec3f &v3f);
    
    Vec3i operator-(const Vec3i &v3) const;
    
    inline long double length() const
    {
        return std::sqrt((long double)(x * x + y * y + z * z));
    }
    
    int x;
    int y;
    int z;
};
