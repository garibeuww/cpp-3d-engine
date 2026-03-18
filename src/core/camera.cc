#include "camera.h"
#include <cmath>

Camera::Camera()
{
    position = Vec3(0.0f, 0.0f, 3.0f);

    yaw = -1.57f; // -90 graus
    pitch = 0.0f;

    fov = 45.0f;
}

Vec3 Camera::GetFront()
{
    Vec3 front;

    front.x = cos(yaw) * cos(pitch);
    front.y = sin(pitch);
    front.z = sin(yaw) * cos(pitch);

    front.normalize();
    return front;
}

Mat4 Camera::GetViewMatrix()
{
    Vec3 front = GetFront();
    Vec3 target = position + front;

    return Mat4::LookAt(position, target, Vec3(0,1,0));
}

Mat4 Camera::GetProjection(float aspect)
{
    float rad = fov * 3.14159f / 180.0f;
    return Mat4::Perspective(rad, aspect, 0.1f, 100.0f);
}