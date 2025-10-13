#include <glad/glad.h>
#include <PRISM/Renderer/Renderer.h>
#include <PRISM/Utils/FLoader.h>
#include <glm/gtc/matrix_transform.hpp>

Renderer::Renderer(const std::shared_ptr<Camera>& p_camera, const std::shared_ptr<Window>& p_window)
{
    // Create a default shader and use it
    currentShader = std::make_unique<Shader>(FLoader::LoadFile("shaders/default.vert"),
                                             FLoader::LoadFile("shaders/default.frag"));
    // Initialize It
    currentShader->Initialize();
    // Enable it
    currentShader->Enable();

    //Enable Depth
    glEnable(GL_DEPTH_TEST);
}
void Renderer::BeginFrame()
{
    // Update camera and view matrices
    currentShader->UpdateMatrix(MatrixType::MatrixProjection, camera->GetProjectionMatrix());
    currentShader->UpdateMatrix(MatrixType::MatrixView, camera->GetViewMatrix());

    // Start frame
    window->PollEvents();
    window->Clear();
}

void Renderer::Draw(const Model &model)
{
    // Create model identity matrix
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    // Use model data to move,rotate and scale
    modelMatrix = glm::translate(modelMatrix, model.GetPosition());

    // Inform the shader of the change
    currentShader->UpdateMatrix(MatrixType::MatrixModel, modelMatrix);

    model.Draw();
}

void Renderer::EndFrame()
{
    window->SwapBuffers();
}
