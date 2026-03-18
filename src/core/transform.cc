#include "transform.h"

Transform::Transform()
{
    position = Vec3(0.0f, 0.0f, 0.0f);
    rotation = Vec3(0.0f, 0.0f, 0.0f);
    scale = Vec3(1.0f, 1.0f, 1.0f);
}

Mat4 Transform::GetMatrix() const
{
    Mat4 translation = Mat4::Translation(position);

    Mat4 rotX = Mat4::RotationX(rotation.x);
    Mat4 rotY = Mat4::RotationY(rotation.y);
    Mat4 rotZ = Mat4::RotationZ(rotation.z);

    Mat4 rotationMat = rotZ * rotY * rotX;

    Mat4 scaleMat = Mat4::Scale(scale);

    return translation * rotationMat * scaleMat;
}