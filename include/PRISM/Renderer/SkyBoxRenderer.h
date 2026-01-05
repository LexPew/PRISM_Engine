#pragma once
#include <PRISM/Renderer/Cube.h>
#include <PRISM/Renderer/Shader.h>
#include <PRISM/Renderer/CubeMap.h>
#include <memory>
class SkyBoxRenderer
{
private:
    std::shared_ptr<CubeMap> skyBoxTexture{nullptr}; // Current SkyBox Texture
    std::shared_ptr<Cube> cubeMesh{nullptr};       // 1X1 Cube Mesh for rendering the skybox
    std::shared_ptr<Shader> skyBoxShader{nullptr}; // Current SkyBox Shader
public:
    SkyBoxRenderer();
    void DrawSkyBox(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);
    void SetSkyboxShader(const std::string &vertexSource, const std::string &fragmentSource);

};