#include <PRISM/Examples/CubeScene.h>
#include <PRISM/Renderer/Cube.h>
#include <PRISM/Engine/OrbitalCameraEntity.h>
#include <PRISM/Engine/ModelEntity.h>
#include <PRISM/Utils/PMath.h>
#include <PRISM/Examples/RubiksCubeExample.h>

#include <PRISM/Core/AssetManger.h>

#include <PRISM/Engine/Terrain.h>
std::shared_ptr<OrbitalCameraEntity> camera;
void CubeScene::Start()
{
    camera = std::make_shared<OrbitalCameraEntity>();
    camera->transform.position = {0, 0, 15.0f};
    AddEntity(camera);

    // Create one Cube instance that stays in scope
    auto rubixCube = std::make_shared<RubiksCubeExample>();

    auto monkeyMesh = AssetManager::LoadMesh("examples/Monkey.obj");
    auto cubeMesh = std::make_shared<Cube>();
    auto boxTexture = AssetManager::LoadTexture("examples/crate1/crate1_diffuse.png");

    for (int i = 0; i < 10; i++)
    {
        auto newCube = std::make_shared<ModelEntity>();

        float rX = PMath::RandomRange(-5, 5);
        float rY = PMath::RandomRange(-5, 5);
        float rZ = PMath::RandomRange(-5, 5);

        float rand = PMath::RandomRange(0.0f, 1.0f);
        // Randomly choose between cubeMesh, cubeMesh2, and objMesh
        if (rand <= 0.33f)
        {
            newCube->SetMesh(cubeMesh);
        }

        else if (rand < 0.66f)
        {
            newCube->SetMesh(rubixCube);
            newCube->SetTexture(boxTexture);
        }
        else
        {
            newCube->SetMesh(monkeyMesh);
        }

        newCube->transform.position = {rX, rY, rZ};
        newCube->transform.scale = {1, 1, 1};
        AddEntity(newCube);
    }
    Scene::Start();
}
void CubeScene::Update(float deltaTime)
{
    for (auto &entity : GetEntities())
    {
        if (entity.get() != camera.get()) // Don't rotate the camera
        {
            entity->transform.rotation.y += deltaTime * 10.0f;
            entity->transform.rotation.x += deltaTime * 20.0f;
        }
    }
    Scene::Update(deltaTime);
}