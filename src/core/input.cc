#include "input.h"

GLFWwindow* Input::window = nullptr;

void Input::Init(GLFWwindow* win)
{
    window = win;
}

bool Input::IsKeyPressed(int key)
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}