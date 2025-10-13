#pragma once
#include <PRISM/Renderer/Model.h>
#include <PRISM/Renderer/Camera.h>
#include <PRISM/Core/Window.h>
#include <PRISM/Renderer/Shader.h>

#include <memory>
//Renderer handles all rendering related stuff, wrapping over opengl etc
class Renderer
{
private:
    std::shared_ptr<Camera> camera; //Need a camera for rendering
    std::shared_ptr<Window> window; //Current window
    std::unique_ptr<Shader> currentShader; //Currently active shader
public:
    //Renderer needs camera and window for matrices and for resize callbacks
    Renderer(const std::shared_ptr<Camera>& p_camera, const std::shared_ptr<Window>& p_window);

    void BeginFrame(); //Start of a frame

    void Draw(const Model& model);
    
    void EndFrame(); //End of a frame
};