#pragma once
#include <PRISM/Core/Input/Mouse.h>
#include <GLFW/glfw3.h>

/**
 * @class Input
 * @brief Handles keyboard and mouse input for the PRISM engine.
 *
 * The Input class manages user input from both the keyboard and mouse.
 * It supports cursor locking/unlocking for gameplay, mouse movement tracking,
 * and interaction with the GUI through ImGui.  
 * 
 * This class follows a singleton pattern (accessible through Input::Get())
 * to provide a global input interface.
 */
class Input
{
private:
    /**
     * @brief Mouse instance used to track position, movement, and button states.
     */
    Mouse mouse;

    /**
     * @brief Tracks whether the cursor is currently locked (disabled) or unlocked (visible).
     */
    bool cursorLocked{false};

    /**
     * @brief Private constructor to enforce singleton pattern.
     */
    Input() {};

public:
    /**
     * @brief Retrieves the global Input instance.
     * @return Reference to the active Input singleton.
     */
    static Input& Get()
    {
        static Input instance;
        return instance;
    }

    /**
     * @brief Updates the input system for the current frame.
     * 
     * This includes processing mouse movement, handling keyboard presses,
     * updating ImGui input (conditionally), and camera/gameplay input.
     * @param window Pointer to the GLFW window for polling input.
     */
    void Update(GLFWwindow* window);

    /**
     * @brief Ends the frame for the input system.
     * 
     * Clears per-frame values in the Mouse instance, preparing for the next frame.
     */
    void EndFrame()
    {
        mouse.EndFrame();
    }

    /**
     * @brief Retrieves the Mouse instance.
     * @return Reference to the mouse object.
     */
    Mouse& GetMouse() { return mouse; }

    /**
     * @brief Checks whether a specific key is currently pressed.
     * @param keyCode GLFW key code to check (e.g., GLFW_KEY_W).
     * @return True if the key is pressed, false otherwise.
     */
    bool IsKeyPressed(int keyCode)
    {
        return glfwGetKey(glfwGetCurrentContext(), keyCode) == GLFW_PRESS;
    }

    /**
     * @brief Locks or unlocks the mouse cursor.
     * 
     * When locked, the cursor is disabled and hidden, typically for gameplay
     * camera control. When unlocked, the cursor is visible and free for GUI interaction.
     * @param lock True to lock the cursor, false to unlock.
     */
    void SetCursorLockState(bool lock);

    /**
     * @brief Toggles the current cursor lock state.
     * 
     * Switches between locked (gameplay) and unlocked (GUI) modes.
     */
    void ToggleCursorLock();

    /**
     * @brief Checks whether the cursor is currently locked.
     * @return True if the cursor is locked, false if unlocked.
     */
    bool IsCursorLocked() { return cursorLocked; }
};
