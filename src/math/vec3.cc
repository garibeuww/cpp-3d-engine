#include "vec3.h"

Vec3::Vec3()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

Vec3::Vec3(float value)
{
    x = value;
    y = value;
    z = value;
}

Vec3::Vec3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

float Vec3::magnitude() const
{
    return std::sqrt(x*x + y*y + z*z);
}

float Vec3::sqrMagnitude() const
{
    return x*x + y*y + z*z;
}

void Vec3::normalize()
{
    float len = magnitude();

    if (len == 0.0f)
        return;

    float inv = 1.0f / len;

    x *= inv;
    y *= inv;
    z *= inv;
}

Vec3 Vec3::normalized() const
{
    float len = magnitude();

    if (len == 0.0f)
        return Vec3(0.0f);

    float inv = 1.0f / len;

    return Vec3(
        x * inv,
        y * inv,
        z * inv
    );
}

float Vec3::dot(const Vec3& v) const
{
    return x*v.x + y*v.y + z*v.z;
}

Vec3 Vec3::cross(const Vec3& v) const
{
    return Vec3(
        y*v.z - z*v.y,
        z*v.x - x*v.z,
        x*v.y - y*v.x
    );
}

Vec3 Vec3::operator+(const Vec3& v) const
{
    return Vec3(x + v.x, y + v.y, z + v.z);
}

Vec3 Vec3::operator-(const Vec3& v) const
{
    return Vec3(x - v.x, y - v.y, z - v.z);
}

Vec3 Vec3::operator*(float scalar) const
{
    return Vec3(x * scalar, y * scalar, z * scalar);
}

Vec3 Vec3::operator/(float scalar) const
{
    return Vec3(x / scalar, y / scalar, z / scalar);
}