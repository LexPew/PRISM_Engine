#include <PRISM/Core/Input/Input.h>
#include <GLFW/glfw3.h>
#include <PRISM/Core/Window.h>

Input *Input::Instance = nullptr;
Input::Input()
{
    Instance = this;
}
void Input::SetCursorLockState(bool lock)
{
    cursorLocked = lock;
    glfwSetInputMode(Window::Get()->GetGlfwWindow(), GLFW_CURSOR, lock ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}
