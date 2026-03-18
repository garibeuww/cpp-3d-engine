#include "renderer.h"
#include <glad/glad.h>
#include "renderer.h"
#include "../scene/entity.h"
#include "../core/camera.h"
#include "../math/mat4.h"
#include "mesh.h"

void Renderer::Draw(Entity& e, Camera& camera)
{
    if (!e.mesh || !e.material) return;

	e.material->Bind();

	Mat4 model = e.transform.GetMatrix();
	Mat4 view = camera.GetViewMatrix();
	Mat4 projection = camera.GetProjection(16.0f / 9.0f);

	e.material->shader->SetMat4("model", model.Data());
	e.material->shader->SetMat4("view", view.Data());
	e.material->shader->SetMat4("projection", projection.Data());

	e.mesh->Draw();
}