#include "Vec3i.h"

Vec3i::Vec3i(int x, int y, int z)
    : x(x), y(y), z(z)
{
}

Vec3i::Vec3i(const Vec3f &v3f)
    : x((int)(v3f.x + 0.5L)), y((int)(v3f.y + 0.5L)), z((int)(v3f.z + 0.5L))
{
}

Vec3i Vec3i::operator-(const Vec3i &v3) const
{
    return Vec3i(x - v3.x, y - v3.y, z - v3.z);
}
