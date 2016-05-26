#pragma once

#include "../DWin3DLib_global.h"
#include <cmath>

struct DWIN3DLIB_API Vec2i
{
public:
    explicit Vec2i(int x, int y);
    
    inline long double length() const
    {
        return std::sqrt((long double)(x * x + y * y));
    }
    
    int x;
    int y;
};
