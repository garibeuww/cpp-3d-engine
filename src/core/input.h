#pragma once
#include <GLFW/glfw3.h>

class Input
{
public:
    static void Init(GLFWwindow* win);

    static bool IsKeyPressed(int key);

private:
    static GLFWwindow* window;
};