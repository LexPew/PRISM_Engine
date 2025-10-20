#include <PRISM/Core/Input/Mouse.h>
#include <PRISM/Renderer/Renderer.h>
#include <PRISM/Core/Input/Input.h>
#include <PRISM/Core/Window.h>

Mouse::Mouse()
{
    glfwSetScrollCallback(Window::Get()->GetGlfwWindow(), ScrollCallback);
}

void Mouse::Update(GLFWwindow* window)
{
    CalculateMouseDelta(window);
    UpdateMouseButtons(window);
}

bool Mouse::GetMouseButtonDown(int mouseButton)
{
    switch (mouseButton)
    {
        case 0: return leftDown;
        case 1: return rightDown;
        default: return false;
    }
}

void Mouse::UpdateMouseButtons(GLFWwindow* window)
{
    leftDown  = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1);
    rightDown = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2);
}

void Mouse::CalculateMouseDelta(GLFWwindow* window)
{
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);

    glm::vec2 currentMousePos(static_cast<float>(xPos), static_cast<float>(yPos));
    mouseDelta = currentMousePos - lastMousePosition;
    lastMousePosition = currentMousePos;
}

void Mouse::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    Input::Instance->GetMouse().SetScrollDelta(static_cast<float>(yoffset));
}

void Mouse::EndFrame()
{
    scrollDelta = 0.0f;
}
