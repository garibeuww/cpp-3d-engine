#pragma once
#include <cmath>

class Vec3
{
public:
    float x;
    float y;
    float z;

    Vec3();
    Vec3(float value);
    Vec3(float x, float y, float z);

    float magnitude() const;
    float sqrMagnitude() const;

    void normalize();
    Vec3 normalized() const;

    float dot(const Vec3& v) const;
    Vec3 cross(const Vec3& v) const;

    Vec3 operator+(const Vec3& v) const;
    Vec3 operator-(const Vec3& v) const;
    Vec3 operator*(float scalar) const;
    Vec3 operator/(float scalar) const;
};