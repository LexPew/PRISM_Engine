#pragma once
#include <GLFW/glfw3.h>

class Time
{
public:
    static float deltaTime;
    static float elapsedTime;

    static void Update()
    {
        static double lastTime = glfwGetTime();
        double currentTime = glfwGetTime();

        deltaTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;
        elapsedTime += deltaTime;
    }
};

