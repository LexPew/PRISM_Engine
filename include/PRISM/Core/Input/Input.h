#pragma once
#include <PRISM/Core/Input/Mouse.h>
//TODO: Write proper input handling
class Input
{
private:
    Mouse mouse;
public:
    static Input* Instance;
    Input();
    void Update(GLFWwindow* window)
    {
        mouse.Update(window);
    };
    //Used for clearing values
    void EndFrame(){ 
        mouse.EndFrame();
    }
    Mouse& GetMouse(){return mouse;}

    bool IsKeyPressed(int keyCode){
        return glfwGetKey(glfwGetCurrentContext(), keyCode) == GLFW_PRESS;
    }
};

