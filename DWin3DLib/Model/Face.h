#pragma once

#include "../DWin3DLib_global.h"

struct DWIN3DLIB_API Face
{
public:
    explicit Face();
    explicit Face(int v1, int v2, int v3);
    
    int v1;
    int v2;
    int v3;
};
