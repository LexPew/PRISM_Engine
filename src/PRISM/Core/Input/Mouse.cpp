#include <PRISM/Core/Input/Mouse.h>
#include <PRISM/Renderer/Renderer.h>
#include <PRISM/Core/Input/Input.h>
#include <PRISM/Core/Window.h>


Mouse::Mouse()
{
    glfwSetScrollCallback(Window::Get()->GetGlfwWindow(), ScrollCallback);
}

void Mouse::Update(GLFWwindow *window)
{
    // Calcualte Delta

    CalculateMouseDelta(window);
    UpdateMouseButtons(window);
}
bool Mouse::GetMouseButtonDown(int mouseButton)
{
    switch (mouseButton)
    {
    case 1:
        return leftDown;
        break;
    case 2:
        return rightDown;
        break;
    default:
        return false;
    };
}

void Mouse::UpdateMouseButtons(GLFWwindow *window)
{
    leftDown = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1);
    rightDown = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2);
}

void Mouse::CalculateMouseDelta(GLFWwindow *window)
{
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    glm::vec2 currentMousePos((float)xPos, (float)yPos);

    mouseDelta = lastMousePosition - currentMousePos;

    lastMousePosition = currentMousePos;
}


void Mouse::ScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
    Input::Instance->GetMouse().SetScrollDelta((float)yoffset);
}
void Mouse::EndFrame()
{
    scrollDelta = 0;
}