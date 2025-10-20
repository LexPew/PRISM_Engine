#pragma once
#include <PRISM/Core/Input/Mouse.h>
// TODO: Write proper input handling
class Input
{
private:
    Mouse mouse;
    bool cursorLocked { false};

public:
    static Input *Instance;
    Input();
    void Update(GLFWwindow *window)
    {
        if (IsKeyPressed(GLFW_KEY_ESCAPE))
        {
            //Set mouse cursor to unlock 
            SetCursorLockState(false);
        }
        mouse.Update(window);
    };
    // Used for clearing values
    void EndFrame()
    {
        mouse.EndFrame();
    }
    Mouse &GetMouse() { return mouse; }

    bool IsKeyPressed(int keyCode)
    {
        return glfwGetKey(glfwGetCurrentContext(), keyCode) == GLFW_PRESS;
    }

    // Cursor Locking & Visibility
    void SetCursorLockState(bool lock);

    void ToggleCursorLock() { SetCursorLockState(!cursorLocked); };
};
