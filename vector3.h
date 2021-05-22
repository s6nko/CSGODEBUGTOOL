#include <algorithm>
#define PI 3.1415927f

struct vec3
{
    float x, y, z;

    vec3 Subtract(vec3 src, vec3 dst)
    {
        vec3 diff;
        diff.x = src.x - dst.x;
        diff.y = src.y - dst.y;
        diff.z = src.z - dst.z;
        return diff;
    }

    float Magnitude(vec3 vec)
    {
        return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    }

    float Distance(vec3 src, vec3 dst)
    {
        vec3 diff = Subtract(src, dst);
        return Magnitude(diff);
    }

    vec3 CalcAngle(vec3 src, vec3 dst)
    {
        vec3 angle;
        angle.x = -atan2f(dst.x - src.x, dst.y - src.y) / PI * 180.0f + 180.0f;
        angle.y = asinf((dst.z - src.z) / Distance(src, dst)) * 180.0f / PI;
        angle.z = 0.0f;

        return angle;
    }

};
