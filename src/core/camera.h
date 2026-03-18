#pragma once

#include "../math/vec3.h"
#include "../math/mat4.h"

class Camera
{
public:
    Vec3 position;

    float yaw;
    float pitch;
    float fov;

    float sensitivity = 0.01f;

    Camera();

    Mat4 GetViewMatrix();
    Mat4 GetProjection(float aspect);

    Vec3 GetFront();
};