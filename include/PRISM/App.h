#pragma once

#include <glad/glad.h>

#include <PRISM/Renderer/Renderer.h>
#include <PRISM/Core/Window.h>
#include <PRISM/Engine/CameraEntity.h>
#include <memory>
//App Is Responsible for managing PRISM app lifecycle
//NOTE: App should never really have to touch raw opengl use wrappers!
class App
{
private:
    std::shared_ptr<Window> window{nullptr};



    int screenWidth = 800.0f;
    int screenHeight = 600.0f;
    float fov = 45.0f;

public:
    bool Init();
    bool Run();

private:
    void Loop();
};