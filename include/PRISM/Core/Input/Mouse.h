#pragma once
#include <glm/vec2.hpp>
#include <GLFW/glfw3.h>
// Mouse Recieves its data via glfw window when update is called

class Mouse
{
private:
    glm::vec2 lastMousePosition{0,0};
    glm::vec2 mouseDelta{0,0};

    bool leftDown{false};
    bool rightDown{false};
    float scrollDelta{0};
public:
    Mouse();

    void Update(GLFWwindow *window);

    glm::vec2 GetPosition(){return lastMousePosition;};
    bool GetMouseButtonDown(int mouseButton);
    const glm::vec2& GetMouseDelta() const {return mouseDelta; };
    void SetScrollDelta(float delta){scrollDelta = delta;};
    float GetScrollDelta(){return scrollDelta;};
    void EndFrame();

    bool ImGuiCursorCheck();

private:
    //Calculates the mouse delta
    void CalculateMouseDelta(GLFWwindow *window);
    void UpdateMouseButtons(GLFWwindow*window);
    static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};