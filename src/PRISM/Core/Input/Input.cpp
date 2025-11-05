#include <PRISM/Core/Input/Input.h>
#include <GLFW/glfw3.h>
#include <PRISM/Core/Window.h>



void Input::Update(GLFWwindow * window)
    {
        if (IsKeyPressed(GLFW_KEY_ESCAPE))
        {
            // Set mouse cursor to unlock
            SetCursorLockState(false);
        }

     
        mouse.Update(window);
    };

void Input::SetCursorLockState(bool lock)
{
    cursorLocked = lock;
    glfwSetInputMode(Window::Get()->GetGlfwWindow(), GLFW_CURSOR, lock ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

void Input::ToggleCursorLock()
{
    // Toggle the cursor lock state and set whether we can interact with the GUI or not.
    bool currentState = IsCursorLocked();
    SetCursorLockState(!currentState);

}
