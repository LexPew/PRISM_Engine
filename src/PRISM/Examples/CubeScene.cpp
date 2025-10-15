#include <PRISM/Examples/CubeScene.h>
#include <PRISM/Renderer/Cube.h>
#include <PRISM/Engine/OrbitalCameraEntity.h>
#include <PRISM/Engine/ModelEntity.h>
#include <PRISM/Utils/PMath.h>
#include <fmt/core.h>
std::shared_ptr<OribitalCameraEntity> camera;
void CubeScene::Start()
{
    camera = std::make_shared<OribitalCameraEntity>();
    camera->transform.position = {0, 0, 15.0f};
    AddEntity(camera);

    // Create one Cube instance that stays in scope
    static Cube cubeMesh; // <-- static ensures it stays alive for the whole program

    for (int i = 0; i < 10; i++)
    {
        auto newCube = std::make_shared<ModelEntity>();

        float rX = PMath::RandomRange(-5, 5);
        float rY = PMath::RandomRange(-5, 5);
        float rZ = PMath::RandomRange(-5, 5);

        newCube->SetMesh(cubeMesh); // Pass by reference, copy by value
        newCube->transform.position = {rX, rY, rZ};
        newCube->transform.scale = {1, 1, 1};
        AddEntity(newCube);
    }
    Scene::Start();
}
void CubeScene::Update(float deltaTime)
{
    for (auto& entity : GetEntities())
    {
        if (entity.get() != camera.get()) // Don't rotate the camera
        {
            entity->transform.rotation.y += deltaTime * 10.0f;
            entity->transform.rotation.x += deltaTime * 20.0f; 
        }
    }
    Scene::Update(deltaTime);
}