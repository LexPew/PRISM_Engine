#pragma once
#include <PRISM/Renderer/Shader.h>
#include <PRISM/Engine/CameraEntity.h>
#include <PRISM/Renderer/Mesh.h>
#include <memory>

/**
 * @class Renderer
 * @brief Core rendering system responsible for managing shaders, drawing meshes, and controlling the render pipeline.
 *
 * The Renderer class encapsulates the rendering process for the PRISM engine.
 * It handles shader management, camera matrix updates, and the drawing of meshes.
 *
 * This class follows a singleton pattern (accessible through Renderer::Get())
 * and provides a simple interface for beginning a frame, drawing 3D objects, and ending a frame.
 */
class Renderer
{
private:
    /**
     * @brief The currently active shader used for rendering.
     */
    std::unique_ptr<Shader> currentShader;

    /**
     * @brief Singleton instance of the Renderer.
     */
    static Renderer* instance;

public:
    /**
     * @brief Retrieves the global Renderer instance.
     * @return Pointer to the active Renderer.
     */
    static Renderer* Get() { return instance; }

    /**
     * @brief Constructs the Renderer and initializes rendering resources.
     */
    Renderer();

    /**
     * @brief Updates the active shader with the latest camera matrices.
     * @param camera Pointer to the camera entity used for projection and view matrices.
     */
    void SendCameraMatrices(const CameraEntity* camera);

    /**
     * @brief Begins a new frame.
     *
     * Polls window events and clears the screen. This should be called before any draw calls.
     */
    void BeginFrame();

    /**
     * @brief Draws a mesh with the specified transformation.
     * @param model Reference to the mesh to draw.
     * @param position World-space position of the mesh.
     * @param rotation Euler rotation (in degrees).
     * @param scale Scale factor of the mesh.
     */
    void Draw(const Mesh& model, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);

    /**
     * @brief Ends the current frame.
     *
     * Swaps display buffers. This should be called after all draw calls for the frame.
     */
    void EndFrame();
};
