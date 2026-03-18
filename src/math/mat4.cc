#include "mat4.h"

Mat4::Mat4()
{
    for (int i = 0; i < 16; i++)
        data[i] = 0.0f;
}

Mat4 Mat4::Identity()
{
    Mat4 result;

    result.data[0] = 1.0f;
    result.data[5] = 1.0f;
    result.data[10] = 1.0f;
    result.data[15] = 1.0f;

    return result;
}

Mat4 Mat4::Translation(const Vec3& position)
{
    Mat4 result = Mat4::Identity();

    result.data[12] = position.x;
    result.data[13] = position.y;
    result.data[14] = position.z;

    return result;
}

Mat4 Mat4::Scale(const Vec3& scale)
{
    Mat4 result = Mat4::Identity();

    result.data[0] = scale.x;
    result.data[5] = scale.y;
    result.data[10] = scale.z;

    return result;
}

Mat4 Mat4::RotationX(float angle)
{
    Mat4 result = Mat4::Identity();

    float c = cos(angle);
    float s = sin(angle);

    result.data[5] = c;
    result.data[6] = s;
    result.data[9] = -s;
    result.data[10] = c;

    return result;
}

Mat4 Mat4::RotationY(float angle)
{
    Mat4 result = Mat4::Identity();

    float c = cos(angle);
    float s = sin(angle);

    result.data[0] = c;
    result.data[2] = -s;
    result.data[8] = s;
    result.data[10] = c;

    return result;
}

Mat4 Mat4::RotationZ(float angle)
{
    Mat4 result = Mat4::Identity();

    float c = cos(angle);
    float s = sin(angle);

    result.data[0] = c;
    result.data[1] = s;
    result.data[4] = -s;
    result.data[5] = c;

    return result;
}

Mat4 Mat4::operator*(const Mat4& other) const
{
    Mat4 result;

    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            result.data[col + row * 4] =
                data[0 + row * 4] * other.data[col + 0 * 4] +
                data[1 + row * 4] * other.data[col + 1 * 4] +
                data[2 + row * 4] * other.data[col + 2 * 4] +
                data[3 + row * 4] * other.data[col + 3 * 4];
        }
    }

    return result;
}

Mat4 Mat4::Perspective(float fov, float aspect, float near, float far)
{
    Mat4 result;

    float tanHalfFov = tan(fov / 2.0f);

    result.data[0] = 1.0f / (aspect * tanHalfFov);
    result.data[5] = 1.0f / tanHalfFov;
    result.data[10] = -(far + near) / (far - near);
    result.data[11] = -1.0f;
    result.data[14] = -(2.0f * far * near) / (far - near);

    return result;
}

Mat4 Mat4::LookAt(const Vec3& eye, const Vec3& target, const Vec3& up)
{
	Vec3 forward = (target - eye).normalized();
    Vec3 right = forward.cross(up).normalized();
    Vec3 camUp = right.cross(forward);

    Mat4 result = Mat4::Identity();

    result.data[0] = right.x;
    result.data[4] = right.y;
    result.data[8] = right.z;

    result.data[1] = camUp.x;
    result.data[5] = camUp.y;
    result.data[9] = camUp.z;

    result.data[2] = -forward.x;
    result.data[6] = -forward.y;
    result.data[10] = -forward.z;

    result.data[12] = -right.dot(eye);
    result.data[13] = -camUp.dot(eye);
    result.data[14] = forward.dot(eye);

    return result;
}
