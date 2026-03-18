#include "application.h"
#include "../scene/scene.h"
#include "../scene/entity.h"
#include "../graphics/renderer.h"
#include "../graphics/shader.h"
#include "../graphics/mesh.h"
#include "../graphics/texture.h"
#include "../graphics/material.h"
#include "../assets/resource_manager.h"
#include "../math/mat4.h"
#include "../math/vec3.h"
#include "camera.h"
#include "input.h"

#include <glad/glad.h>
#include <iostream>

Renderer renderer;
Shader* shader;
Mesh* cubeMesh;
Texture* texture;
Material* material;
Camera camera;
Scene scene;

Entity cubeEntity;

float lastX = 960;
float lastY = 540;
bool firstMouse = true;

Application::Application()
{
    Init();
}

void Application::Init()
{
    glfwInit();

    window = glfwCreateWindow(1920, 1080, "Engine", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glEnable(GL_DEPTH_TEST);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
    Input::Init(window);
	
	shader = ResourceManager::LoadShader(
		"default",
		"../../src/assets/shaders/vert.glsl",
		"../../src/assets/shaders/frag.glsl"
	);
	
	texture = ResourceManager::LoadTexture("white", "../../src/assets/crate.jpg");
	material = ResourceManager::CreateMaterial("mat1");
	//Shader* shader = new Shader(vs, fs);

	cubeMesh = ResourceManager::LoadMesh("cube", "../../src/assets/cube.obj");

	if (!cubeMesh)
	{
		std::cout << "ERRO: mesh null" << std::endl;
	}

    // CRIAR TEXTURA DE VERDADE
    //texture = new Texture("../../src/assets/crate.jpg");

	material->shader = shader;
	material->texture = texture;

    // CONFIGURAR ENTITY
    cubeEntity.mesh = cubeMesh;
    cubeEntity.transform.position = Vec3(0,0,0);
	cubeEntity.material = material;

    // IMPORTANTE: usar ponteiro
    scene.Add(&cubeEntity);

    shader->Use();
    shader->SetInt("texture1", 0);

    camera.position = Vec3(0, 0, 5);
}

Application::~Application()
{
	ResourceManager::Clear();
    glfwTerminate();
}

void Application::Update(float dt)
{
	cubeEntity.transform.rotation.y += dt;
	
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // invertido

	lastX = xpos;
	lastY = ypos;

	xoffset *= camera.sensitivity;
	yoffset *= camera.sensitivity;

	camera.yaw += xoffset;
	camera.pitch += yoffset;

	// trava o pitch (não virar de cabeça pra baixo)
	if (camera.pitch > 1.5f) camera.pitch = 1.5f;
	if (camera.pitch < -1.5f) camera.pitch = -1.5f;
	
    Vec3 front = camera.GetFront();
	Vec3 right = front.cross(Vec3(0,1,0));
	right.normalize();

	float speed = 2.5f * dt;

	if (Input::IsKeyPressed(GLFW_KEY_W))
		camera.position = camera.position + front * speed;

	if (Input::IsKeyPressed(GLFW_KEY_S))
		camera.position = camera.position - front * speed;

	if (Input::IsKeyPressed(GLFW_KEY_A))
		camera.position = camera.position - right * speed;

	if (Input::IsKeyPressed(GLFW_KEY_D))
		camera.position = camera.position + right * speed;
}

void Application::Render()
{
    glClearColor(0.1f, 0.1f, 0.15f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->Use();

	shader->SetVec3("lightPos", Vec3(2,2,2));
	shader->SetVec3("viewPos", camera.position);

    scene.Render(renderer, camera);
}

void Application::Run()
{
    float lastFrame = 0;

    while (!glfwWindowShouldClose(window))
    {
        float time = glfwGetTime();
        float deltaTime = time - lastFrame;
        lastFrame = time;

        Update(deltaTime);
        Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}