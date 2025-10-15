#include <glad/glad.h>
#include <PRISM/Renderer/Renderer.h>
#include <PRISM/Utils/FLoader.h>
#include <glm/gtc/matrix_transform.hpp>
#include <fmt/core.h>
#include <PRISM/Renderer/RenderSettings.h>
Renderer* Renderer::Instance = nullptr;


Renderer::Renderer(const std::shared_ptr<Window> &p_window)
{

    Instance = this;
    window = p_window;
    // Create a default shader and use it
    currentShader = std::make_unique<Shader>(FLoader::LoadFile("shaders/default.vert"),
                                             FLoader::LoadFile("shaders/default.frag"));
    // Initialize It
    currentShader->Initialize();
    // Enable it
    currentShader->Enable();

    // Enable Depth
    if(RenderSettings::testDepth)
    {
    glEnable(GL_DEPTH_TEST);
    }

}
void Renderer::BeginFrame()
{

    // Start frame
    window->PollEvents();
    window->Clear();
}


void Renderer::SendCameraMatrices(const CameraEntity* camera)
{
    currentShader->Enable();


    glm::mat4x4 projectionMatrix = glm::perspective(glm::radians(camera->fov), ((float)window->screenWidth / (float)window->screenHeight), camera->near, camera->far);
    
    glm::vec3 targetPosition = camera->transform.position + camera->transform.forward();
    glm::mat4x4 viewMatrix = glm::lookAt(camera->transform.position, targetPosition, {0,1,0});


    // Update camera and view matrices
    currentShader->UpdateMatrix(MatrixType::MatrixProjection, projectionMatrix);
    currentShader->UpdateMatrix(MatrixType::MatrixView, viewMatrix);
}
void Renderer::Draw(const Mesh &model, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
    currentShader->Enable();
    // Create model identity matrix
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    // Use model data to move,rotate and scale
    modelMatrix = glm::translate(modelMatrix, position);

    // Rotation
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), {1, 0, 0});
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), {0, 1, 0});
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), {0, 0, 1});

    //Scale
    modelMatrix = glm::scale(modelMatrix, scale);
    // Inform the shader of the change
    currentShader->UpdateMatrix(MatrixType::MatrixModel, modelMatrix);

    model.Draw();
}

void Renderer::EndFrame()
{
    window->SwapBuffers();
}
