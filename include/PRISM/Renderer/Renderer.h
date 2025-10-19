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
    std::unique_ptr<Shader> currentShader;
    static Renderer *instance;

public:
    static Renderer *Get() { return instance; }

    Renderer();

    void SendCameraMatrices(const CameraEntity *camera);

    void BeginFrame(); // Start of a frame

    void Draw(const Mesh &model, const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale);

    void EndFrame(); // End of a frame
};