#include <PRISM/Core/Input/Mouse.h>
#include <PRISM/Renderer/Renderer.h>

Mouse::Mouse()
{
}

void Mouse::Update(GLFWwindow *window)
{
    // Calcualte Delta
    CalculateMouseDelta(window);
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
    glm::vec2 currentMousePos(xPos, yPos);

    mouseDelta = lastMousePosition - currentMousePos;
}