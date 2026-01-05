#include <PRISM/Renderer/SkyBoxRenderer.h>
#include <PRISM/Utils/FLoader.h>
#include <glad/glad.h>
SkyBoxRenderer::SkyBoxRenderer()
{
    // Default Skybox setup
    cubeMesh = std::make_shared<Cube>();

    skyBoxTexture = std::make_shared<CubeMap>(FLoader::LoadImage(FLoader::GetAssetPath("examples/Cubemap_Sky_04-512x512.png")));
    std::string vert = FLoader::LoadFile(FLoader::GetAssetPath("engine/shaders/skybox.vert"));
    std::string frag = FLoader::LoadFile(FLoader::GetAssetPath("engine/shaders/skybox.frag"));
    skyBoxShader = std::make_shared<Shader>(vert, frag);
    skyBoxShader->Initialize();
    skyBoxShader->SetInt("skybox", 0);

}

void SkyBoxRenderer::DrawSkyBox(const glm::mat4 &projectionMatrix, const glm::mat4 &viewMatrix)
{
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL); // allow skybox (depth=1.0) to pass

    skyBoxShader->Enable();
    skyBoxShader->UpdateMatrix(MatrixType::MatrixProjection, projectionMatrix);

    // remove translation
    glm::mat4 skyViewMatrix = glm::mat4(glm::mat3(viewMatrix));
    skyBoxShader->UpdateMatrix(MatrixType::MatrixView, skyViewMatrix);

    glActiveTexture(GL_TEXTURE0);
    skyBoxTexture->Bind();
    cubeMesh->Draw();

    glDepthFunc(GL_LESS); // restore default
    glDepthMask(GL_TRUE);
}
void SkyBoxRenderer::SetSkyboxShader(const std::string &vertexSource, const std::string &fragmentSource)
{
    skyBoxShader = std::make_shared<Shader>(vertexSource, fragmentSource);
    skyBoxShader->Initialize();
}