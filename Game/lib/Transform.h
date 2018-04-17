#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <array>
using namespace std;

struct Transform
{
    float matrix[16];

    Transform();
    Transform(array<float, 16> mat);

    Transform inverse() const;

    static Transform translation(float x, float y, float z);
    static Transform rotationXZ(float angle);
    static Transform rotationYZ(float angle);
};

Transform operator*(const Transform &a, const Transform &b);

#endif // TRANSFORM_H

