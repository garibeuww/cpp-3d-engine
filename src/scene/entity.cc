#include "entity.h"

Mat4 Entity::GetModelMatrix()
{
    return Mat4::Translation(transform.position)
        * Mat4::RotationY(transform.rotation.y)
        * Mat4::Scale(transform.scale);
}