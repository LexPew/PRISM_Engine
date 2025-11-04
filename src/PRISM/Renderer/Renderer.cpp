#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include <PRISM/Core/Window.h>
#include <PRISM/Renderer/Renderer.h>
#include <PRISM/Renderer/RenderSettings.h>
#include <PRISM/Utils/FLoader.h>


// TODO: UPDATE THIS TO USE BETTER THAN RUNTIME ERROR AND SORT INCLUDES ETC
Renderer::Renderer()
{
    currentShader = std::make_unique<Shader>(
        
        FLoader::LoadFile(FLoader::GetAssetPath("engine/shaders/default.vert")),
        FLoader::LoadFile(FLoader::GetAssetPath("engine/shaders/default.frag"))
    );

    currentShader->Initialize();
    currentShader->Enable();

    if (RenderSettings::testDepth)
        glEnable(GL_DEPTH_TEST);
}

void Renderer::BeginFrame()
{
    Window::Get()->PollEvents();
    Window::Get()->Clear();
}

void Renderer::SendCameraMatrices(const CameraEntity* camera)
{
    currentShader->Enable();

    projectionMatrix = glm::perspective(
        glm::radians(camera->fov),
        (float)(Window::Get()->GetScreenWidth()) /
        (float)(Window::Get()->GetScreenHeight()),
        camera->near,
        camera->far
    );

    projectionMatrix = projectionMatrix;

    glm::vec3 targetPosition = camera->transform.position + camera->transform.forward();
    viewMatrix = glm::lookAt(camera->transform.position, targetPosition, {0, 1, 0});



    currentShader->UpdateMatrix(MatrixType::MatrixProjection, projectionMatrix);
    currentShader->UpdateMatrix(MatrixType::MatrixView, viewMatrix);
}

void Renderer::Draw(const std::shared_ptr<Mesh>& model, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
    currentShader->Enable();

    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), {1, 0, 0});
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), {0, 1, 0});
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), {0, 0, 1});
    modelMatrix = glm::scale(modelMatrix, scale);

    currentShader->UpdateMatrix(MatrixType::MatrixModel, modelMatrix);
    model->Draw();
}

void Renderer::EndFrame()
{
    Window::Get()->SwapBuffers();
}
