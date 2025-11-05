#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include <PRISM/Core/Window.h>
#include <PRISM/Renderer/Renderer.h>
#include <PRISM/Renderer/RenderSettings.h>

#include <PRISM/Utils/FLoader.h>
#include <glm/gtc/type_ptr.hpp>
#include <fmt/core.h>

// TODO: UPDATE THIS TO USE BETTER THAN RUNTIME ERROR AND SORT INCLUDES ETC
Renderer::Renderer()
{
    currentShader = std::make_unique<Shader>(

        FLoader::LoadFile(FLoader::GetAssetPath("engine/shaders/default.vert")),
        FLoader::LoadFile(FLoader::GetAssetPath("engine/shaders/default.frag")));

    currentShader->Initialize();
    currentShader->Enable();

    if (RenderSettings::testDepth)
        glEnable(GL_DEPTH_TEST);
}

void Renderer::Initialize()
{
    
    for (int i = 0; i < maxLights; i++)
    {
        lightStatus.insert(std::make_pair(i,true));
        SetLightEnabled(i, false);
    }
}

void Renderer::BeginFrame()
{
    Window::Get()->PollEvents();
    Window::Get()->Clear();
}

void Renderer::SendCameraMatrices(const CameraEntity *camera)
{
    currentShader->Enable();

    projectionMatrix = glm::perspective(
        glm::radians(camera->fov),
        (float)(Window::Get()->GetScreenWidth()) /
            (float)(Window::Get()->GetScreenHeight()),
        camera->near,
        camera->far);

    projectionMatrix = projectionMatrix;

    glm::vec3 targetPosition = camera->transform.position + camera->transform.forward();
    viewMatrix = glm::lookAt(camera->transform.position, targetPosition, {0, 1, 0});

    currentShader->UpdateMatrix(MatrixType::MatrixProjection, projectionMatrix);
    currentShader->UpdateMatrix(MatrixType::MatrixView, viewMatrix);
}

void Renderer::SetSceneLighting(const SceneLighting &sceneLighting)
{
    currentShader->Enable();

    // Update ambient light
    unsigned int ambientLocation = glGetUniformLocation(currentShader->GetProgramId(), "ambient_Light");
    if (ambientLocation != -1)
    {
        glUniform3fv(ambientLocation, 1, glm::value_ptr(sceneLighting.ambientLightColour));
    }
    else
    {
        fmt::print("Warning: 'ambient_Light' uniform not found in shader.\n");
    }
    // Update directional light
    unsigned int directionalLocation = glGetUniformLocation(currentShader->GetProgramId(), "directional_Light");
    if (directionalLocation != -1)
    {
        glUniform3fv(directionalLocation, 1, glm::value_ptr(sceneLighting.directionalLight.direction));
    }
    else
    {
        fmt::print("Warning: 'directional_Light' uniform not found in shader.\n");
    }
}
void Renderer::Draw(const std::shared_ptr<Mesh> &model, const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale)
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

void Renderer::ShutDown()
{
    currentShader = nullptr;
}

int Renderer::RequestLightId()
{
    if (idCounter < maxLights)
    {
        idCounter++;
        return (idCounter - 1);
    }
    return -1;
}

void Renderer::SendLightDetails(const unsigned int lightId, const glm::vec3 &position, const float intensity)
{
    // Build the uniform name for this light
    std::string lightPrefix = "lights[" + std::to_string(lightId) + "]";

    // Send light position
    int lightPositionLocation = glGetUniformLocation(currentShader->GetProgramId(), (lightPrefix + ".light_position").c_str());
    if (lightPositionLocation != -1)
    {
        glUniform3fv(lightPositionLocation, 1, glm::value_ptr(position));
    }

    // Send light intensity
    int lightIntensityLocation = glGetUniformLocation(currentShader->GetProgramId(), (lightPrefix + ".light_intensity").c_str());
    if (lightIntensityLocation != -1)
    {
        glUniform1f(lightIntensityLocation, intensity);
    }
}

void Renderer::SetLightEnabled(unsigned int lightId, bool enabled)
{
    if (lightId < maxLights)
    {
     // Update internal light status
    auto lightIt = lightStatus.find(lightId);
    if (lightIt != lightStatus.end())
    {
        lightIt->second = enabled;
    }



        std::string lightPrefix = "lights[" + std::to_string(lightId) + "]";
        // Send light position
        int lightActiveLocatoin = glGetUniformLocation(currentShader->GetProgramId(), (lightPrefix + ".active").c_str());
        if (lightActiveLocatoin != -1)
        {
            glUniform1i(lightActiveLocatoin, enabled);
        }
    }
}