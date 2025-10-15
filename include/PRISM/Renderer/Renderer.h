#pragma once
#include <PRISM/Core/Window.h>
#include <PRISM/Renderer/Shader.h>
#include <PRISM/Engine/CameraEntity.h>
#include <PRISM/Renderer/Mesh.h>
#include <memory>
//Renderer handles all rendering related stuff, wrapping over opengl etc
class Renderer
{
private:
    //std::shared_ptr<Camera> camera; //Need a camera for rendering
    std::shared_ptr<Window> window; //Current window
    std::unique_ptr<Shader> currentShader; //Currently active shader
public:

    static Renderer* Instance;

    //Renderer needs camera and window for matrices and for resize callbacks
    Renderer(const std::shared_ptr<Window>& p_window);

    void SendCameraMatrices(const CameraEntity* camera);

    void BeginFrame(); // Start of a frame



    void Draw(const Mesh &model, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
    
    void EndFrame(); //End of a frame

    const std::shared_ptr<Window>& GetWindow(){ return window; };
};