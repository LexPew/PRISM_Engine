#include <PRISM/Engine/Scene.h>

#include <PRISM/Engine/Entity.h>
#include <PRISM/Renderer/Renderer.h>
#include <imgui.h>

void Scene::Start()
{
    for (auto &entity : entities)
    {
        entity->Start();
    }
}

void Scene::Update(float deltaTime)
{
    for (auto &entity : entities)
    {
        entity->Update(deltaTime);
    }
}
void Scene::Draw()
{
    // Send Scene lighting to renderer
    Renderer::Get().SetSceneLighting(sceneLighting);

    //TODO: CHANGE THIS TO USE SCENE SKYBOX IF EXISTS AND MAKE IT MORE FLEXIBLE
    // Draw Skybox 
    Renderer::Get().DrawSkyBox();

    for (auto &entity : entities)
    {
        entity->Draw();
    }
}
