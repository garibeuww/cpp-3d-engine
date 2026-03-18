#pragma once
#include "../math/vec3.h"
#include "../math/mat4.h"

class Transform
{
public:
    Vec3 position;
    Vec3 rotation;
    Vec3 scale;

    Transform();

    Mat4 GetMatrix() const;
};